/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:27:01 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/04 18:02:41 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_pos_and_orinetation(t_map *m, t_player *p)
{
	int		j;
	int		i;
	char	c;

	i = 0;
	while (m -> map[i])
	{
		j = 0;
		while (m -> map[i][j])
		{
			c = m -> map[i][j];
			if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
			{
				p->pos_row = (double)i + 0.5;
				p->pos_col = (double)j + 0.5;
				m->orientation = c;
			}
			j++;
		}
		i++;
	}
}

void	initialize(t_player *p, t_map *m, t_cubed *cub3d)
{
	int i = 0;
	m->height = HEIGHT;
	m->width = WIDTH;
	m -> map = cub3d -> map;
	init_pos_and_orinetation(m, p);
	p->fov = 0.66;
	p->time = 0;
	p->oldtime = 0;
	initialize_direction(p, m);
	p->mov_speed = 0.05;
	p->rot_speed = 0.03;
	p->pitch = 0;
	p->speed_ratio = 1;
	p->sprint = 1;
	p->plane_x = -p->direct_y * p->fov;
	p->plane_y = p->direct_x * p->fov;
	p->buffer_col = malloc(sizeof(int) * m->width);
	while(i < m->width)
	{
		p->buffer_col[i] = INT_MAX;
		i++;
	}
	m->key->w = 0;
	m->key->s = 0;
	m->key->a = 0;
	m->key->d = 0;
	m->key->left = 0;
	m->key->right = 0;
	m->n_sprites = 0;
	m->tex_height = 0;
	m->tex_width = 0;
}

void	initialize_direction(t_player *p, t_map *m)
{
	if (m->orientation == 'N')
	{
		p->direct_x = 0.0;
		p->direct_y = -1.0;
	}
	if (m->orientation == 'S')
	{
		p->direct_x = 0.0;
		p->direct_y = 1.0;
	}
	if (m->orientation == 'W')
	{
		p->direct_x = -1.0;
		p->direct_y = 0.0;
	}
	if (m->orientation == 'E')
	{
		p->direct_x = 1.0;
		p->direct_y = 0.0;
	}
}
