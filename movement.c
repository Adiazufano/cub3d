/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:25:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/11 15:38:23 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		col_cur;
	int		row_cur;

	margin = 0.1;
	col_cur = (int)(p->pos_col);
	row_cur = (int)(p->pos_row);
	if (m->map[(int)(p->new_pos_row + margin)][col_cur] != '1'
		&& m->map[(int)(p->new_pos_row + margin)][col_cur] != '3'
		&& m->map[(int)(p->new_pos_row - margin)][col_cur] != '1'
		&& m->map[(int)(p->new_pos_row - margin)][col_cur] != '3'
		&& m->map[(int)(p->new_pos_row + 0)][col_cur] != '1'
		)
		p->pos_row = p->new_pos_row;
	if (m->map[row_cur][(int)(p->new_pos_col + margin)] != '1'
		&& m->map[row_cur][(int)(p->new_pos_col + margin)] != '3'
		&& m->map[row_cur][(int)(p->new_pos_col - margin)] != '1'
		&& m->map[row_cur][(int)(p->new_pos_col - margin)] != '3')
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
	mov_colision(m, p);
}
