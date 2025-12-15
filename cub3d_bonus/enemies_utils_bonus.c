/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:32:54 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 17:19:52 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	chek_n_enemies_utils(t_enemy **enemies, t_cubed *cub3d,
			int col, int row)
{
	char	c;

	c = cub3d->map[row][col];
	if (c == 'X')
	{
		*enemies = init_enemy(col, row);
		if (!(*enemies))
		{
			printf("error");
			free_list(cub3d->enemy);
			exit (1);
		}
		lstadd_back_ene(&cub3d->enemy, *enemies);
	}
}
