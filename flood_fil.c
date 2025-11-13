/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:21:34 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/13 14:01:11 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	flood_rec(t_point pos, int rows, char **map, int **visited)
{
	int		rowlen;
	t_point	next;

	if (pos.y < 0 || pos .y >= rows)
		return (1);
	rowlen = (int)ft_strlen(map[pos.y]);
	if (pos.x < 0 || pos.x >= rowlen)
		return (1);
	if (map[pos.y][pos.x] == ' ' || map[pos.y][pos.x] == '\t')
		return (1);
	if (map[pos.y][pos.x] == '1' || visited[pos.y][pos.x] == 1)
		return (0);
	visited[pos.y][pos.x] = 1;
	next.x = pos.x + 1;
	next.y = pos.y;
	if (flood_rec(next, rows, map, visited))
		return (1);
	next.x = pos.x - 1;
	next.y = pos.y;
	if (flood_rec(next, rows, map, visited))
		return (1);
	next.x = pos.x;
	next.y = pos.y + 1;
	if (flood_rec(next, rows, map, visited))
		return (1);
	next.x = pos.x;
	next.y = pos.y - 1;
	if (flood_rec(next, rows, map, visited))
		return (1);
	return (0);
}

void	run_flood_check(t_cubed *cub3d)
{
	size_t	rows;
	size_t	i;
	size_t	j;
	size_t	max_w;
	int		**visited;
	int		start_x;
	int		start_y;
	t_point	start;
	int		result;
	size_t	l;
	char	c;
	size_t	k;

	if (!cub3d || !cub3d -> map)
	{
		printf("Error: missing map\n");
		free_cub3d(cub3d);
		exit(1);
	}
	rows = 0;
	max_w = 0;
	while (cub3d -> map[rows])
	{
		l = ft_strlen(cub3d -> map[rows]);
		if (l > max_w)
			max_w = l;
		rows++;
	}
	if (rows == 0 || max_w == 0)
	{
		printf("Error: empty map\n");
		free_cub3d(cub3d);
		exit(1);
	}
	start_x = -1;
	start_y = -1;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < ft_strlen(cub3d -> map[i]))
		{
			c = cub3d -> map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				start_x = (int)j;
				start_y = (int)i;
				break;
			}
			j++;
		}
		if (start_x >= 0)
			break;
		i++;
	}
	if (start_x < 0)
	{
		printf("Error: Missing playes start\n");
		free_cub3d(cub3d);
		exit(1);
	}
	visited = malloc(sizeof(*visited) * rows);
	if (!visited)
	{
		perror("malloc");
		free_cub3d(cub3d);
		exit(1);
	}
	i = 0;
	while (i < rows)
	{
		visited[i] = malloc(sizeof(**visited) * max_w);
		if (!visited[i])
		{
			k = 0;
			while (k < i)
				free(visited[k++]);
			free(visited);
			perror("malloc");
			free_cub3d(cub3d);
			exit(1);
		}
		j = 0;
		while (j < max_w)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	start.x = start_x;
	start.y = start_y;
	result	= flood_rec(start, (int)rows, cub3d -> map, visited);
	i = 0;
	while (i < rows)
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


