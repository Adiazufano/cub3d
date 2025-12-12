/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:29:44 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/11 16:30:38 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	portal_utilitis_open(t_map *m, int front_row,
			int front_col, t_player *p)
{
	m->portal->last_open_pos_r = front_row;
	m->portal->last_open_pos_c = front_col;
	m->portal->open_player_pos_row = p->pos_row;
	m->portal->open_player_pos_col = p->pos_col;
	m->portal->open_dir_x = p->direct_x * -1.0;
	m->portal->open_dir_y = p->direct_y * -1.0;
	m->portal->open_plane_x = p->plane_x * -1.0;
	m->portal->open_plane_y = p->plane_y * -1.0;
}

void	open_portal(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '1' && m->portal->open_portal == 0)
	{
		m->map[front_row][front_col] = '4';
		portal_utilitis_open(m, front_row, front_col, p);
		m->portal->open_portal++;
	}
	else if (m->map[front_row][front_col] == '1' && m->portal->open_portal == 1)
	{
		m->map[front_row][front_col] = '4';
		m->map[m->portal->last_open_pos_r][m->portal->last_open_pos_c] = '1';
		portal_utilitis_open(m, front_row, front_col, p);
	}
}

void	portal_utilitis_close(t_map *m, int front_row,
			int front_col, t_player *p)
{
	m->portal->last_close_pos_r = front_row;
	m->portal->last_close_pos_c = front_col;
	m->portal->close_player_pos_row = p->pos_row;
	m->portal->close_player_pos_col = p->pos_col;
	m->portal->close_dir_x = p->direct_x * -1.0;
	m->portal->close_dir_y = p->direct_y * -1.0;
	m->portal->close_plane_x = p->plane_x * -1.0;
	m->portal->close_plane_y = p->plane_y * -1.0;
}

void	close_portal(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '1' && m->portal->close_portal == 0)
	{
		m->map[front_row][front_col] = '5';
		portal_utilitis_close(m, front_row, front_col, p);
		m->portal->close_portal++;
	}
	else if (m->map[front_row][front_col] == '1'
				&& m->portal->close_portal == 1)
	{
		m->map[front_row][front_col] = '5';
		m->map[m->portal->last_close_pos_r][m->portal->last_close_pos_c] = '1';
		portal_utilitis_close(m, front_row, front_col, p);
	}
}

void	door(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '3')
		m->map[front_row][front_col] = '2';
	else if (m->map[front_row][front_col] == '2')
		m->map[front_row][front_col] = '3';
}
