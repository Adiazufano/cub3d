/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:32:04 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/15 13:20:48 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_draw_cl(t_tex_bytes *t, t_draw_col *dc, t_map *m, t_player *p)
{
	dc->screen = m->image->pixels;
	dc->screen_w = m->width;
	dc->screen_h = m->height;
	dc->draw_start = p->init_draw;
	dc->draw_end = p->finish_draw;
	dc->line_height = p->line_height;
	dc->side = p->side;
	dc->ray_dir_x = p->dirray_x;
	dc->ray_dir_y = p->dirray_y;
	dc->pitch = p->pitch;
	dc->tex = t;
}

int	raycasting(t_player *p, t_map *m)
{
	if (!m->image || !m->image->pixels)
		return (0);
	raycasting_draw_utils(p, m, m->textures);
	return (1);
}

t_tex_bytes	*select_texture(t_textures *tetxures, t_map *m, t_player *p)
{
	t_tex_bytes	*current;

	current = NULL;
	(void)m;
	if (p->side == 0)
	{
		if (p->step_x > 0)
			current = tetxures->west_texture;
		else
			current = tetxures->east_texture;
	}
	else
	{
		if (p->step_y > 0)
			current = tetxures->north_tetxure;
		else
			current = tetxures->south_texture;
	}
	return (current);
}

void	init_draw_cl(t_tex_bytes *t, t_draw_col *dc, t_map *m, t_player *p)
{
	dc->screen = m->image->pixels;
	dc->screen_w = m->width;
	dc->screen_h = m->height;
	dc->draw_start = p->init_draw;
	dc->draw_end = p->finish_draw;
	dc->line_height = p->line_height;
	dc->side = p->side;
	dc->ray_dir_x = p->dirray_x;
	dc->ray_dir_y = p->dirray_y;
	dc->pitch = p->pitch;
	dc->tex = t;
}
