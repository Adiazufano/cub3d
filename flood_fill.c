/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:21:34 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/15 10:44:45 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_expand(t_point *pos, char **map, int **visited)
{
	t_point	next;

	next = *pos;
	next.x = pos->x + 1;
	next.y = pos->y;
	if (flood_rec(&next, map, visited))
		return (1);
	next = *pos;
	next.x = pos->x - 1;
	next.y = pos->y;
	if (flood_rec(&next, map, visited))
		return (1);
	next = *pos;
	next.x = pos->x;
	next.y = pos->y + 1;
	if (flood_rec(&next, map, visited))
		return (1);
	next = *pos;
	next.x = pos->x;
	next.y = pos->y - 1;
	if (flood_rec(&next, map, visited))
		return (1);
	return (0);
}

int	flood_rec(t_point *pos, char **map, int **visited)
{
	int		rowlen;
	char	ch;

	if (pos->y < 0 || pos->y >= (int)pos->rows)
		return (1);
	if (!map[pos->y])
		return (1);
	rowlen = (int)ft_strlen(map[pos->y]);
	if (pos->x < 0 || pos->x >= rowlen)
		return (1);
	ch = map[pos->y][pos->x];
	if (ch == ' ' || ch == '\t')
		return (1);
	if (ch == '1' || visited[pos->y][pos->x] == 1)
		return (0);
	visited[pos->y][pos->x] = 1;
	return (flood_expand(pos, map, visited));
}

void	get_start_pos(t_cubed *cub3d, t_point *start)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < (int)start->rows)
	{
		j = 0;
		while (j < (int)ft_strlen(cub3d->map[i]))
		{
			c = cub3d->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				start->start_x = (int)j;
				start->start_y = (int)i;
				break ;
			}
			j++;
		}
		if (start->start_x >= 0)
			break ;
		i++;
	}
}

static void	check_map_and_start(t_cubed *cub3d, t_point *start)
{
	if (!cub3d || !cub3d->map)
	{
		printf("Error: missing map\n");
		free_cub3d(cub3d);
		exit(1);
	}
	init_flood_filll(start);
	width_and_height(cub3d, start);
	check_n_players(cub3d);
	get_start_pos(cub3d, start);
	if (start->start_x < 0)
	{
		printf("Error: Missing playes start\n");
		free_cub3d(cub3d);
		exit(1);
	}
	start->x = start->start_x;
	start->y = start->start_y;
}

void	run_flood_check(t_cubed *cub3d)
{
	size_t	i;
	int		**visited;
	t_point	start;
	int		result;

	check_map_and_start(cub3d, &start);
	if (alloc_visited(&visited, &start, cub3d) < 0)
	{
		printf("malloc failed\n");
		free_cub3d(cub3d);
		exit(1);
	}
	result = flood_rec(&start, cub3d->map, visited);
	i = 0;
	while (i < start.rows)
		free(visited[i++]);
	free(visited);
	if (result)
	{
		printf("Error: map not closed\n");
		free_cub3d(cub3d);
		get_next_line(-1);
		exit(1);
	}
}
