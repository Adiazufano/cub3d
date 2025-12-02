/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:18:34 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:41:00 by mparra-s         ###   ########.fr       */
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
		*lst = new;
	else
	{
		last = *lst;
		while (last -> next)
			last = last -> next;
		last -> next = new;
	}
}

void init_enemy(t_enemy *e, int col, int row)
{
	e->pos_x = col;
	e->pos_y = row;
	e->life = 3;
	e->next = NULL;
    e->screen_x = 0;
	e->sprite_height = 0;
	e->sprite_width = 0;
	e->draw_start_x = 0;
	e->draw_end_x = 0;
	e->draw_start_y = 0;
	e->draw_end_y = 0;
	e->dx = 0;
	e->dy = 0;
	e->transform_x = 0;
	e->transform_y = 0;
}

void    check_n_enemies(t_enemy **enemies, t_cubed *cub3d)
{
    t_enemy *node;
    int     col;
    int     row;
    char    c;
    
    row= 0;
    while (cub3d->map[row])
	{
		col = 0;
		while (cub3d->map[row][col])
		{
			c = cub3d->map[row][col];
			if (c == 'X')
            {
                node = malloc (sizeof (t_enemy));
                if (!node)
                {
                    free_list(*enemies);
                    return ;                                       
                }
				init_enemy(node, col, row);

                lstadd_back_ene(enemies, node);                            
            }
			col++;
		}
		row++;
	}
}
