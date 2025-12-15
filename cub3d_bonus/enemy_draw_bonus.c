/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:49:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 18:52:04 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	setup_draw_sprite(t_enemy *e, t_map *m, t_tex_info **out_ti)
{
	t_tex_info	*ti;

	if (!e || !m || !m->texture_info)
		return (0);
	ti = m->texture_info;
	if (e->tex_id < 0 || e->tex_id >= ti->count)
		return (0);
	*out_ti = ti;
	m->helper->margin = e->transform_y * 0.01;
	m->helper->stripe = e->draw_start_x;
	m->helper->tex_width = ti->widths[e->tex_id];
	m->helper->tex_height = ti->heights[e->tex_id];
	return (1);
}

void	compute_tex_x(t_enemy *e, t_map *m, int stripe)
{
	m->helper->sprite_l = e->screen_x - e->sprite_width / 2;
	m->helper->tex_x = (stripe - m->helper->sprite_l)
		* m->helper->tex_width / e->sprite_width;
	if (m->helper->tex_x < 0)
		m->helper->tex_x = 0;
	if (m->helper->tex_x >= m->helper->tex_width)
		m->helper->tex_x = m->helper->tex_width - 1;
}

int	sprite_visible_at_stripe(t_player *p, t_enemy *e,
		t_map *m, int stripe)
{
	if (e->transform_y <= 0)
		return (0);
	if (stripe < 0 || stripe >= m->width)
		return (0);
	if (e->transform_y >= p->buffer_col[stripe] - m->helper->margin)
		return (0);
	return (1);
}

void	draw_sprite_column(t_enemy *e, t_map *m,
	t_tex_info *ti, int stripe)
{
	uint32_t	color;
	int			y;
	int			d;

	y = e->draw_start_y;
	while (y < e->draw_end_y)
	{
		d = (y - e->draw_start_y) * m->helper->tex_height;
		m->helper->tex_y = d / e->sprite_height;
		if (m->helper->tex_y < 0)
			m->helper->tex_y = 0;
		if (m->helper->tex_y >= m->helper->tex_height)
			m->helper->tex_y = m->helper->tex_height - 1;
		color = ti->pixeles[e->tex_id]
		[m->helper->tex_y * m->helper->tex_width + m->helper->tex_x];
		m->helper->alpha = (color >> 24) & 0xFF;
		if (m->helper->alpha != 0)
			mlx_put_pixel(m->image, (uint32_t)stripe, (uint32_t)y, color);
		y++;
	}
}

void	draw_sprite(t_player *p, t_enemy *e, t_map *m)
{
	t_tex_info	*ti;
	int			stripe;

	if (!setup_draw_sprite(e, m, &ti))
		return ;
	stripe = m->helper->stripe;
	while (stripe < e->draw_end_x)
	{
		compute_tex_x(e, m, stripe);
		if (sprite_visible_at_stripe(p, e, m, stripe))
			draw_sprite_column(e, m, ti, stripe);
		stripe++;
	}
}
