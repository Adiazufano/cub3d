/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:58:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:11:22 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bubble_pass(t_enemy **enemy, t_enemy **lptr)
{
	t_enemy	**ptr;
	t_enemy	*tmp;
	int		swapped;

	ptr = enemy;
	swapped = 0;
	while ((*ptr)->next != *lptr)
	{
		if ((*ptr)->enemy_distance < (*ptr)->next->enemy_distance)
		{
			tmp = (*ptr)->next;
			(*ptr)->next = tmp->next;
			tmp->next = *ptr;
			*ptr = tmp;
			swapped = 1;
		}
		else
			ptr = &(*ptr)->next;
	}
	*lptr = *ptr;
	return (swapped);
}

void	sort_enemies(t_enemy **enemy)
{
	t_enemy	*lptr;
	int		swapped;

	if (!enemy || !*enemy)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
		swapped = bubble_pass(enemy, &lptr);
}
