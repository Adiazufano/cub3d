/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:53:34 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 18:55:00 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	map_is_wall(t_map *m, int mx, int my)
{
	if (!m || !m->map)
		return (1);
	if (my < 0 || mx < 0)
		return (1);
	if (!m->map[my])
		return (1);
	if (m->map[my][mx] == '\0')
		return (1);
	return (m->map[my][mx] == '1');
}

static int	tile_collision(t_map *m, double x, double y, double radius)
{
	double	nx;
	double	ny;
	double	dx;
	double	dy;

	nx = fmax(m->helper->tx, fmin(x, m->helper->tx + 1.0));
	ny = fmax(m->helper->ty, fmin(y, m->helper->ty + 1.0));
	dx = x - nx;
	dy = y - ny;
	return (dx * dx + dy * dy < radius * radius);
}

int	is_solid(t_map *m, double x, double y, double radius)
{
	int	oy;
	int	ox;

	if (!m || !m->map)
		return (1);
	m->helper->tile_x = (int)floor(x);
	m->helper->tile_y = (int)floor(y);
	oy = -1;
	while (oy <= 1)
	{
		ox = -1;
		while (ox <= 1)
		{
			m->helper->tx = m->helper->tile_x + ox;
			m->helper->ty = m->helper->tile_y + oy;
			if (map_is_wall(m, m->helper->tx, m->helper->ty)
				&& tile_collision(m, x, y, radius))
				return (1);
			ox++;
		}
		oy++;
	}
	return (0);
}

int	enemy_can_see_player(t_player *p, t_enemy *e, t_map *m, double max_dist)
{
	double	t;

	if (!p || !e || !m)
		return (0);
	m->helper->vx2 = p->pos_col - e->pos_x;
	m->helper->vy2 = p->pos_row - e->pos_y;
	m->helper->dist = sqrt(m->helper->vx2 * m->helper->vx2
			+ m->helper->vy2 * m->helper->vy2);
	m->helper->step = 0.1;
	if (m->helper->dist > max_dist)
		return (0);
	if (m->helper->dist < 1e-6)
		return (1);
	m->helper->vx2 /= m->helper->dist;
	m->helper->vy2 /= m->helper->dist;
	t = 0.0;
	while (t < m->helper->dist)
	{
		m->helper->nx = e->pos_x + m->helper->vx2 * t;
		m->helper->ny = e->pos_y + m->helper->vy2 * t;
		if (map_is_wall(m, (int)m->helper->nx, (int)m->helper->ny))
			return (0);
		t += m->helper->step;
	}
	return (1);
}
