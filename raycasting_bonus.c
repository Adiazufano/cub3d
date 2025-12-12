/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:54:48 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 09:22:30 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	raycasting_init(t_player *p)
{
	p->hit = 0;
	p->map_x = (int)p->pos_col;
	p->map_y = (int)p->pos_row;
	if (p->dirray_x < 0)
	{
		p->step_x = -1;
		p->side_dist_x = (p->pos_col - p->map_x) * p->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		p->side_dist_x = (p->map_x - p->pos_col + 1) * p->delta_dist_x;
	}
	if (p->dirray_y < 0)
	{
		p->step_y = -1;
		p->side_dist_y = (p->pos_row - p->map_y) * p->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		p->side_dist_y = (p->map_y - p->pos_row + 1) * p->delta_dist_y;
	}
}

void	raycasting_dda(t_player *p, t_map *m)
{
	while (p->hit == 0)
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->side_dist_x += p->delta_dist_x;
			p->map_x += p->step_x;
			p->side = 0;
		}
		else
		{
			p->side_dist_y += p->delta_dist_y;
			p->map_y += p->step_y;
			p->side = 1;
		}
		if (p->map_y < 0 || p->map_y >= m->height
			|| p->map_x < 0 || p->map_x >= m->width)
		{
			p->hit = 1;
			break ;
		}
		if (is_block(map_at(m, p->map_y, p->map_x)))
			p->hit = 1;
	}
}

void	raycasting_wall(t_player *p, t_map *m, int x)
{
	if (p->side == 0)
		p->perp_wall_dist = p->side_dist_x - p->delta_dist_x;
	else
		p->perp_wall_dist = p->side_dist_y - p->delta_dist_y;
	p->line_height = (int)(m->height / p->perp_wall_dist);
	p->init_draw = -p->line_height / 2 + m->height / 2 - p->pitch;
	if (p->init_draw < 0)
		p->init_draw = 0;
	p->finish_draw = p->line_height / 2 + m->height / 2 - p->pitch;
	if (p->finish_draw >= m->height)
		p->finish_draw = m->height - 1;
	if (x >= 0 && x<= m->width)
		p->buffer_col[x] = p->perp_wall_dist;
}

void	raycasting_draw(t_player *p, t_map *m, int x, t_tex_bytes *tex)
{
	t_draw_col	dc;
	double		wallx;

	if (p->side == 0)
		wallx = p->pos_row + p->perp_wall_dist * p->dirray_y;
	else
		wallx = p->pos_col + p->perp_wall_dist * p->dirray_x;
	if (!isfinite(wallx))
		wallx = 0.0;
	else
	{
		wallx -= floor(wallx);
		if (wallx < 0.0)
			wallx += 1.0;
	}
	init_draw_cl(tex, &dc, m, p);
	dc.x = x;
	dc.wallx = wallx;
	if (dc.screen && dc.tex && dc.line_height > 0
		&& dc.draw_start <= dc.draw_end)
	{
		draw_textured_column_no_pack(&dc);
		return ;
	}
}

void	raycasting_draw_utils(t_player *p, t_map *m, t_textures *textures)
{
	t_tex_bytes	*current;
	int			x;

	x = 0;
	while (x < m->width)
	{
		p->camera_x = (2 * x / (double)m->width) - 1;
		p->dirray_x = p->direct_x + p->plane_x * p->camera_x;
		p->dirray_y = p->direct_y + p->plane_y * p->camera_x;
		if (p->dirray_x == 0)
			p->delta_dist_x = 1e30;
		else
			p->delta_dist_x = fabs(1 / p->dirray_x);
		if (p->dirray_y == 0)
			p->delta_dist_y = 1e30;
		else
			p->delta_dist_y = fabs(1 / p->dirray_y);
		raycasting_init(p);
		raycasting_dda(p, m);
		raycasting_wall(p, m, x);
		current = select_texture(textures, m, p);
		raycasting_draw(p, m, x, current);
		x++;
	}
}
