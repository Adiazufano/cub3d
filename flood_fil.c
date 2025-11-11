/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:58:02 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/11 11:34:41 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error_and_exit(t_cub3d *cub3d)
{
	ft_printf("Error\n");
	free_memory(cub3d -> map, cub3d -> visited_map, game -> map_height);
	cleanup_mlx_resources(game);
	get_next_line(-1);
	exit(1);
}

void	map_errors(int map_fd, t_game *game)
{
	if (map_fd < 0)
		ft_error_and_exit(game);
}

void	flood_fil(t_point *pos, int saltos,
			char **map, int **visited_map)
{
	int		len;
	t_point	next_pos;

	len = ft_strlen(map[0]);
	if (pos -> x < 0 || pos -> x >= len
		|| pos -> y < 0 || pos -> y >= saltos
		|| map[pos -> y][pos -> x] == '1'
		|| visited_map[pos -> y][pos -> x] == 1)
		return ;
	visited_map[pos -> y][pos -> x] = 1;
	next_pos.x = pos -> x + 1;
	next_pos.y = pos -> y;
	flood_fil(&next_pos, saltos, map, visited_map);
	next_pos.x = pos -> x - 1;
	next_pos.y = pos -> y;
	flood_fil(&next_pos, saltos, map, visited_map);
	next_pos.x = pos -> x;
	next_pos.y = pos -> y + 1;
	flood_fil(&next_pos, saltos, map, visited_map);
	next_pos.x = pos -> x;
	next_pos.y = pos -> y - 1;
	flood_fil(&next_pos, saltos, map, visited_map);
}
