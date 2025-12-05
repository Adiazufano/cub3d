/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:18:34 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/04 12:08:10 by mparra-s         ###   ########.fr       */
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

t_enemy	*init_enemy(int col, int row)
{
	t_enemy *e = malloc(sizeof(t_enemy));
    if (!e)
		return NULL;
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
	e->enemy_distance = 0;
	e->dx = 0;
	e->dy = 0;
	e->transform_x = 0;
	e->transform_y = 0;
	e->tex_id = 0;
	return (e);
}

void    check_n_enemies(t_enemy *enemies, t_cubed *cub3d)
{
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
				enemies = init_enemy(col, row);
                if (!enemies)
                {
					printf("error");
                    free_list(cub3d->enemy);
                    exit (1);                                       
                }
                lstadd_back_ene(&cub3d->enemy, enemies);                            
            }
			col++;
		}
		row++;
	}
}
