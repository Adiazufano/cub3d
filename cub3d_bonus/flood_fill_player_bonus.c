/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_player_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:10:49 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:05:03 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_n_players(t_cubed *cub3d)
{
	int		col;
	int		row;
	char	c;
	int		player;

	row = 0;
	player = 0;
	while (cub3d->map[row])
	{
		col = 0;
		while (cub3d->map[row][col])
		{
			c = cub3d->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player++;
			if (player > 1)
			{
				printf("Error: have more than 1 player\n");
				free_cub3d(cub3d);
				exit(1);
			}
			col++;
		}
		row++;
	}
}
