/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_size_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:52:36 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:11:35 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	safe_tz(double tz)
{
	if (tz == 0.0)
		return (1e-6);
	return (tz);
}

static int	clamp_int(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

void	size_correlation(t_enemy *e, t_map *m)
{
	double	tz;
	double	w;
	int		half_w;

	tz = safe_tz(e->transform_y);
	w = 0.85;
	e->screen_x = (int)((m->width / 2) * (1 + e->transform_x / tz));
	e->sprite_height = abs((int)(m->height / tz));
	if (e->sprite_height <= 0)
		e->sprite_height = 1;
	e->sprite_width = fabs((int)(m->height / tz) * w);
	if (e->sprite_width <= 0)
		e->sprite_width = 1;
	half_w = e->sprite_width / 2;
	e->draw_start_x = clamp_int(e->screen_x - half_w, 0, m->width - 1);
	e->draw_end_x = clamp_int(e->screen_x + half_w, 0, m->width - 1);
	e->draw_start_y = clamp_int(-e->sprite_height / 2 + m->height / 2,
			0, m->height - 1);
	e->draw_end_y = clamp_int(e->sprite_height / 2 + m->height / 2,
			0, m->height - 1);
}
