/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:59:28 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:11:16 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	enemy_position(t_player *p, t_enemy *e)
{
	double	inv_det;

	e->dx = e->pos_x - p->pos_col;
	e->dy = e->pos_y - p->pos_row;
	inv_det = 1.0 / (p->plane_x * p->direct_y - p->direct_x * p->plane_y);
	e->transform_x = inv_det * (p->direct_y * e->dx - p->direct_x * e->dy);
	e->transform_y = inv_det * (-p->plane_y * e->dx + p->plane_x * e->dy);
	e->enemy_distance = e->dx * e->dx + e->dy * e->dy;
}

static void	update_all_enemy_positions(t_player *p, t_enemy *head)
{
	t_enemy	*it;

	if (!p || !head)
		return ;
	it = head;
	while (it)
	{
		enemy_position(p, it);
		it = it->next;
	}
}

static void	animate_enemies(t_enemy *head)
{
	t_enemy	*it;
	int		animar;

	if (!head)
		return ;
	it = head;
	while (it)
	{
		animar = (it->speed > 0.001);
		if (it->life > 0 && animar)
		{
			it->e_walk_count++;
			if (it->e_walk_count >= ENEMY_FRAME_TICKS)
			{
				it->anim_frame = (it->anim_frame + 1) % 6;
				it->e_walk_count = 0;
			}
		}
		it->tex_id = it->anim_frame;
		it = it->next;
	}
}

static void	draw_visible_enemies(t_player *p, t_enemy *head, t_map *m)
{
	t_enemy	*it;

	if (!p || !m || !head)
		return ;
	it = head;
	while (it)
	{
		if (it->transform_y > 0)
		{
			size_correlation(it, m);
			draw_sprite(p, it, m);
		}
		it = it->next;
	}
}

int	raycasting_enemy(t_player *p, t_enemy **enemy, t_map *m)
{
	if (!p || !enemy || !m)
		return (0);
	update_all_enemy_positions(p, *enemy);
	update_enemies(p, enemy, m, 0.016);
	update_all_enemy_positions(p, *enemy);
	sort_enemies(enemy);
	animate_enemies(*enemy);
	draw_visible_enemies(p, *enemy, m);
	return (1);
}
