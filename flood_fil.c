/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:21:34 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/26 13:14:53 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

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
	if (ch == '3')
	{
		visited[pos->y][pos->x] = 3;
		return (0);
	}
	visited[pos->y][pos->x] = 1;
	return (flood_expand(pos, map, visited));
}

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

void	width_and_height(t_cubed *cub3d, t_point *start)
{
	size_t	l;

	while (cub3d->map[start->rows])
	{
		l = ft_strlen(cub3d->map[start->rows]);
		if (l > start->max_w)
			start->max_w = l;
		start->rows++;
	}
	if (start->rows == 0 || start->max_w == 0)
	{
		printf("Error: empty map\n");
		free_cub3d(cub3d);
		exit(1);
	}
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

void	free_partial_visited(int **visited, int n)
{
	int	k;

	k = 0;
	while (k < n)
		free(visited[k++]);
	free(visited);
}

int	alloc_visited(int ***out, t_point *start, t_cubed *cub3d)
{
	int		**visited;
	int		i;
	size_t	len;

	visited = malloc(sizeof(*visited) * start->rows);
	if (!visited)
		return (-1);
	i = 0;
	while (i < (int)start->rows)
	{
		len = ft_strlen(cub3d->map[i]);
		if (len == 0)
			visited[i++] = NULL;
		else 
			visited[i] = malloc(sizeof(**visited) * len);
		if (len != 0 && !visited[i])
		{
			free_partial_visited(visited, i);
			return (-1);
		}
		i++;
	}
	*out = visited;
	return (0);
}

void	free_visited(int **visited, int rows)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	init_flood_fill(t_point *start)
{
	start->rows = 0;
	start->max_w = 0;
	start->start_x = -1;
	start->start_y = -1;
	start->x = 0;
	start->y = 0;
}
static void	check_map_and_start(t_cubed *cub3d, t_point *start)
{
	if (!cub3d || !cub3d->map)
	{
		printf("Error: missing map\n");
		free_cub3d(cub3d);
		exit(1);
	}
	init_flood_fill(start);
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

/*
 * New: run flood check using t_map (uses player pos, width/height if set).
 * Call this when you have a t_map
	* (it will call free_cub3d via map->cub3d on error).
 */
