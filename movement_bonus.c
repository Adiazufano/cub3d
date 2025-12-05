/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:25:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/04 18:46:36 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_pov(t_map *m)
{
	if (m->player->pitch == 0)
	{
		m->player->pitch = 100;
		m->player->fov = 0.66;
		m->player->speed_ratio = 0.5;
	}
	else
	{
		m->player->pitch = 0;
		m->player->fov = 0.66;
		m->player->speed_ratio = 1.0;
	}
}

void	rotation(t_map *m)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;
	int			i;

	i = 0;
	p = m->player;
	if (m->key->right)
		i = 1;
	else if (m->key->left)
		i = -1;
	old_dir_x = p->direct_x;
	p->direct_x = p->direct_x * cos(p->rot_speed * i)
		- p->direct_y * sin(p->rot_speed * i);
	p->direct_y = old_dir_x * sin(p->rot_speed * i)
		+ p->direct_y * cos(p->rot_speed * i);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(p->rot_speed * i)
		- p->plane_y * sin(p->rot_speed * i);
	p->plane_y = old_plane_x * sin(p->rot_speed * i)
		+ p->plane_y * cos(p->rot_speed * i);
}

void	movement_keys(t_map *m, t_player *p)
{
	p->new_pos_col = p->pos_col;
	p->new_pos_row = p->pos_row;
	if (m->key->w)
	{
		p->new_pos_col += p->direct_x * p->mov_speed;
		p->new_pos_row += p->direct_y * p->mov_speed;
	}
	if (m->key->s)
	{
		p->new_pos_col -= p->direct_x * p->mov_speed;
		p->new_pos_row -= p->direct_y * p->mov_speed;
	}
	if (m->key->d)
	{
		p->new_pos_col -= p->direct_y * p->mov_speed;
		p->new_pos_row += p->direct_x * p->mov_speed;
	}
	if (m->key->a)
	{
		p->new_pos_col += p->direct_y * p->mov_speed;
		p->new_pos_row -= p->direct_x * p->mov_speed;
	}
}

void	mov_colision(t_map *m, t_player *p)
{
	double	margin;

	margin = 0.1;
	if (((m->map[(int)(p->new_pos_row + margin)][(int)p->pos_col] != '1'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1')
		&& (m->map[(int)(p->new_pos_row - margin)][(int)p->pos_col] != '1'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1'))
		&& ((m->map[(int)(p->new_pos_row + margin)][(int)p->pos_col] != '3'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3')
		&& (m->map[(int)(p->new_pos_row - margin)][(int)p->pos_col] != '3'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3')))
		p->pos_row = p->new_pos_row;
	if (((m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1')
		&& (m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1'))
		&& ((m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3')
		&& (m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3'
		&& m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3')))
		p->pos_col = p->new_pos_col;
}

void	movement(t_map *m)
{
	t_player	*p;
	double		diff;
	int			sprint;

	p = m->player;
	if (p->sprint)
		sprint = 2;
	else
		sprint = 1;
	p->oldtime = p->time;
	p->time = mlx_get_time();
	diff = p->time - p->oldtime;
	p->mov_speed = diff * 3.0 * p->speed_ratio * sprint;
	if (p->mov_speed > 1)
		p->mov_speed = 1;
	movement_keys(m, p);
	rotation(m);
	rotation_mouse(m);
	mov_colision(m, p);
}
