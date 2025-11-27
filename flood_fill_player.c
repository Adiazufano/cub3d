/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:10:49 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 11:14:45 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
