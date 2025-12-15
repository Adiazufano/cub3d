/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:18:34 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 16:33:11 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_list(t_enemy *zombie)
{
	t_enemy	*tmp;

	while (zombie)
	{
		tmp = zombie;
		zombie = zombie->next;
		free(tmp);
	}
}

void	lstadd_back_ene(t_enemy **lst, t_enemy *new)
{
	t_enemy	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	init_enemy_utils(t_enemy *e)
{
	e->enemy_distance = 0;
	e->dx = 0;
	e->dy = 0;
	e->transform_x = 0;
	e->transform_y = 0;
	e->tex_id = 0;
	e->anim_frame = 0;
	e->e_walk_count = 0;
	e->last_x = e->pos_x;
	e->last_y = e->pos_y;
	e->speed = 0.0;
}

t_enemy	*init_enemy(int col, int row)
{
	t_enemy	*e;

	e = malloc(sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->pos_x = (double)col + 0.5;
	e->pos_y = (double)row + 0.5;
	e->life = 3;
	e->next = NULL;
	e->screen_x = 0;
	e->sprite_height = 0;
	e->sprite_width = 0;
	e->draw_start_x = 0;
	e->draw_end_x = 0;
	e->draw_start_y = 0;
	e->draw_end_y = 0;
	init_enemy_utils(e);
	return (e);
}

void	check_n_enemies(t_enemy *enemies, t_cubed *cub3d)
{
	int		col;
	int		row;

	row = 0;
	while (cub3d->map[row])
	{
		col = 0;
		while (cub3d->map[row][col])
		{
			chek_n_enemies_utils(&enemies, cub3d, col, row);
			col++;
		}
		row++;
	}
}
