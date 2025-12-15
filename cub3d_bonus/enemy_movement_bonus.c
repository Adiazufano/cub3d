/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:55:52 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:11:09 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_enemy_towards_player(t_player *p, t_enemy *e, t_map *m, double dt)
{
	m->helper->speed = 1.5;
	m->helper->radius = 0.35;
	m->helper->vx = p->pos_col - e->pos_x;
	m->helper->vy = p->pos_row - e->pos_y;
	m->helper->len = sqrt(m->helper->vx * m->helper->vx
			+ m->helper->vy * m->helper->vy);
	if (m->helper->len < 1e-6)
		return ;
	m->helper->vx /= m->helper->len;
	m->helper->vy /= m->helper->len;
	m->helper->move_x = m->helper->vx * m->helper->speed * dt;
	m->helper->move_y = m->helper->vy * m->helper->speed * dt;
	m->helper->new_x = e->pos_x + m->helper->move_x;
	m->helper->new_y = e->pos_y + m->helper->move_y;
	if (!is_solid(m, m->helper->new_x, m->helper->new_y, m->helper->radius))
	{
		e->pos_x = m->helper->new_x;
		e->pos_y = m->helper->new_y;
		return ;
	}
	if (!is_solid(m, m->helper->new_x, e->pos_y, m->helper->radius))
		e->pos_x = m->helper->new_x;
	if (!is_solid(m, e->pos_x, m->helper->new_y, m->helper->radius))
		e->pos_y = m->helper->new_y;
}

void	update_enemy_speeds(t_enemy *head)
{
	t_enemy	*it;
	double	dx;
	double	dy;

	if (!head)
		return ;
	it = head;
	while (it)
	{
		dx = it->pos_x - it->last_x;
		dy = it->pos_y - it->last_y;
		it->speed = sqrt(dx * dx + dy * dy);
		it->last_x = it->pos_x;
		it->last_y = it->pos_y;
		it = it->next;
	}
}

void	process_enemies(t_player *p, t_enemy *head, t_map *m, double dt)
{
	t_enemy	*it;

	if (!p || !head || !m)
		return ;
	it = head;
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

void	update_enemies(t_player *p, t_enemy **enemy_head, t_map *m, double dt)
{
	if (!p || !enemy_head || !m)
		return ;
	update_enemy_speeds(*enemy_head);
	process_enemies(p, *enemy_head, m, dt);
}
