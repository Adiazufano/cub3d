/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:18:34 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 18:41:24 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void    check_n_enemies(t_cubed *cub3d)
{
    t_enemy *enemies;
    t_enemy *node;
    int     col;
    int     row;
    char    c;
    int count = 0;
    
    enemies = NULL;
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
                    free_list(enemies);
                    return ;                                       
                }
                node->pos_x = col;
                node->pos_y = row;
                node->life = 3;
                node->next = NULL;
                lstadd_back_ene(&enemies, node);
                count++;                                
            }
			col++;
		}
		row++;
	}
    printf("%d", count);
}

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