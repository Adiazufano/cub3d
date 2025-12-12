/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_e_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:20 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 15:13:49 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
void draw_sprite(t_player *p, t_enemy *e, t_map *m)
{
	uint32_t    color;
	t_tex_info *ti;
	double      margin;
	int         stripe;
	int         tex_width;
	int         tex_height;
	int         y;
	int         d;
	int         sprite_l;
	int         tex_x;
	int         tex_y;
	int         alpha;

	if (!e || !m || !m->texture_info)
		return;
	ti = m->texture_info;

	if (e->tex_id < 0 || e->tex_id >= ti->count)
		return;

	margin  = e->transform_y * 0.01;
	stripe = e->draw_start_x;

	tex_width  = ti->widths[e->tex_id];
	tex_height = ti->heights[e->tex_id];

	while (stripe < e->draw_end_x)
	{
		sprite_l = e->screen_x - e->sprite_width / 2;

		tex_x = (stripe - sprite_l) * tex_width / e->sprite_width;
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= tex_width) tex_x = tex_width - 1;

		if (e->transform_y > 0 && stripe >= 0 && stripe < m->width &&
			e->transform_y < p->buffer_col[stripe] - margin)
		{
			y = e->draw_start_y;
			while (y < e->draw_end_y)
			{
				d = (y - e->draw_start_y) * tex_height;
				tex_y = d / e->sprite_height;
				if (tex_y < 0) tex_y = 0;
				if (tex_y >= tex_height) tex_y = tex_height - 1;

				color = ti->pixeles[e->tex_id][tex_y * tex_width + tex_x];
				alpha = (color >> 24) & 0xFF;
				if (alpha != 0)
					mlx_put_pixel(m->image, (uint32_t)stripe, (uint32_t)y, color);
				y++;
			}
		}
		stripe++;
	}
}

void size_correlation(t_enemy *e, t_map *m)
{
	double tz = e->transform_y;
	const double width_scale = 0.85;
	if (tz == 0.0)
		tz = 1e-6;

	e->screen_x = (int)((m->width / 2) * (1 + e->transform_x / tz));
	e->sprite_height = abs((int)(m->height / tz));
	if (e->sprite_height <= 0) e->sprite_height = 1;

	e->sprite_width = fabs((int)(m->height / tz) * width_scale);
	if (e->sprite_width <= 0) e->sprite_width = 1;

	e->draw_start_x = e->screen_x - e->sprite_width / 2;
	if (e->draw_start_x < 0) e->draw_start_x = 0;

	e->draw_end_x = e->screen_x + e->sprite_width / 2;
	if (e->draw_end_x >= m->width) e->draw_end_x = m->width - 1;

	e->draw_start_y = -e->sprite_height / 2 + m->height / 2;
	if (e->draw_start_y < 0) e->draw_start_y = 0;

	e->draw_end_y = e->sprite_height / 2 + m->height / 2;
	if (e->draw_end_y >= m->height) e->draw_end_y = m->height - 1;
}

void sort_enemies(t_enemy **enemy)
{
	t_enemy **ptr;
	t_enemy *lptr;
	t_enemy *tmp;
	int swapped;

	if (!enemy || !*enemy)
		return;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = enemy;
		while ((*ptr)->next != lptr)
		{
			if ((*ptr)->enemy_distance < (*ptr)->next->enemy_distance)
			{
				tmp = (*ptr)->next;
				(*ptr)->next = tmp->next;
				tmp->next = *ptr;
				*ptr = tmp;
				swapped = 1;
			}
			else
				ptr = &(*ptr)->next;
		}
		lptr = *ptr;
	}
}

void enemy_position(t_player *p, t_enemy *e)
{
	double inv_det;

	e->dx = e->pos_x - p->pos_col;
	e->dy = e->pos_y - p->pos_row;
	inv_det = 1.0 / (p->plane_x * p->direct_y - p->direct_x * p->plane_y);
	e->transform_x = inv_det * (p->direct_y * e->dx - p->direct_x * e->dy);
	e->transform_y = inv_det * (-p->plane_y * e->dx + p->plane_x * e->dy);
	e->enemy_distance = e->dx * e->dx + e->dy * e->dy;
}

int map_is_wall(t_map *m, int mx, int my)
{
	if (!m || !m->map)
		return 1;
	if (my < 0 || mx < 0)
		return 1;
	if (!m->map[my])
		return 1;
	if (m->map[my][mx] == '\0')
		return 1;
	return (m->map[my][mx] == '1');
}

int enemy_can_see_player(t_player *p, t_enemy *e, t_map *m, double max_dist)
{
	double vx, vy, dist, step, t, nx, ny;

	if (!p || !e || !m) return 0;

	vx = p->pos_col - e->pos_x;
	vy = p->pos_row - e->pos_y;
	dist = sqrt(vx * vx + vy * vy);
	step = 0.1;

	if (dist > max_dist) return 0;
	if (dist < 1e-6) return 1;

	vx /= dist;
	vy /= dist;
	t = 0.0;
	while (t < dist)
	{
		nx = e->pos_x + vx * t;
		ny = e->pos_y + vy * t;
		if (map_is_wall(m, (int)nx, (int)ny)) return 0;
		t += step;
	}
	return 1;
}

int is_solid(t_map *m, double x, double y, double radius)
{
	int tile_x = (int)floor(x);
	int tile_y = (int)floor(y);

	for (int oy = -1; oy <= 1; oy++)
	for (int ox = -1; ox <= 1; ox++)
	{
		int tx = tile_x + ox;
		int ty = tile_y + oy;

		if (map_is_wall(m, tx, ty))
		{
			// calcular distancia mínima del círculo al tile
			double nearest_x = fmax(tx, fmin(x, tx + 1.0));
			double nearest_y = fmax(ty, fmin(y, ty + 1.0));
			double dx = x - nearest_x;
			double dy = y - nearest_y;

			if (dx*dx + dy*dy < radius * radius)
				return 1; // colisión
		}
	}
	return 0;
}

void move_enemy_towards_player(t_player *p, t_enemy *e, t_map *m, double dt)
{
	const double speed = 1.5;
	const double radius = 0.35;

	double vx = p->pos_col - e->pos_x;
	double vy = p->pos_row - e->pos_y;
	double len = sqrt(vx*vx + vy*vy);
	if (len < 1e-6) return;

	vx /= len;
	vy /= len;

	double move_x = vx * speed * dt;
	double move_y = vy * speed * dt;

	double new_x = e->pos_x + move_x;
	double new_y = e->pos_y + move_y;

	// --- 1. Prueba movimiento completo ---
	if (!is_solid(m, new_x, new_y, radius))
	{
		e->pos_x = new_x;
		e->pos_y = new_y;
		return;
	}

	// --- 2. Prueba solo X (slide) ---
	if (!is_solid(m, new_x, e->pos_y, radius))
		e->pos_x = new_x;

	// --- 3. Prueba solo Y (slide) ---
	if (!is_solid(m, e->pos_x, new_y, radius))
		e->pos_y = new_y;
}

void update_enemies(t_player *p, t_enemy **enemy_head, t_map *m, double dt)
{
	t_enemy *it;

	if (!p || !enemy_head || !m) return;

	it = *enemy_head;

	while (it)
	{
		double dx = it->pos_x - it->last_x;
		double dy = it->pos_y - it->last_y;
		it->speed = sqrt(dx*dx + dy*dy);
		it->last_x = it->pos_x;
		it->last_y = it->pos_y;
		it = it->next;
	}
	it = *enemy_head;
	while (it)
	{
		if (enemy_can_see_player(p, it, m, 12.0))
			move_enemy_towards_player(p, it, m, dt);
		if (it->enemy_distance <= 0.5)
		{
			printf("Game Over\n");
			mlx_close_window(m->mlx);
		}
		it = it->next;
	}
}

int raycasting_enemy(t_player *p, t_enemy **enemy, t_map *m)
{
	t_enemy *tmp;

	if (!p || !enemy || !m)
		return 0;
	tmp = *enemy;
	while (tmp)
	{
		enemy_position(p, tmp);
		tmp = tmp->next;
	}
	update_enemies(p, enemy, m, 0.016);
	tmp = *enemy;
	while (tmp)
	{
		enemy_position(p, tmp);
		tmp = tmp->next;
	}
	sort_enemies(enemy);
	tmp = *enemy;
	while (tmp)
	{
		int animar = 0;
		if (tmp->speed > 0.001)
			animar = 1;

		if (tmp->life > 0 && animar)
		{
			tmp->e_walk_count++;
			if (tmp->e_walk_count >= ENEMY_FRAME_TICKS)
			{
				tmp->anim_frame = (tmp->anim_frame + 1) % 6;
				tmp->e_walk_count = 0;
			}
		}
		tmp->tex_id = tmp->anim_frame;
		tmp = tmp->next;
	}
	tmp = *enemy;
	while (tmp)
	{
		if (tmp->transform_y > 0)
		{
			size_correlation(tmp, m);
			draw_sprite(p, tmp, m);
		}
		tmp = tmp->next;
	}
	return 1;
}
