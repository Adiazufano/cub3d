/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:21:34 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/25 12:09:37 by aldiaz-u         ###   ########.fr       */
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
	if (map[pos.y][pos.x] == '3')
	{
		visited[pos.y][pos.x] = 3;
		return (0);
	}
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

void	check_n_players(t_cubed *cub3d)
{
	int	col;
	int	row;
	char	c;
	int		player;

	row = 0;
	player = 0;
	while (cub3d -> map[row])
	{
		col = 0;
		while (cub3d -> map[row][col])
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
	char	c;
	size_t	k;
	size_t l;
	int	player;

	player = 0;
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
	check_n_players(cub3d);
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

/*
 * New: run flood check using t_map (uses player pos, width/height if set).
 * Call this when you have a t_map * (it will call free_cub3d via map->cub3d on error).
 */
void run_flood_check_map(t_map *map_struct)
{
    size_t	rows = 0;
    size_t	i, j;
    size_t	max_w = 0;
    int		**visited;
    int		start_x = -1;
    int		start_y = -1;
    t_point	start;
    int		result;
    size_t	k;
    char	c;

    if (!map_struct || !map_struct->map)
    {
        fprintf(stderr, "Error: missing map\n");
        if (map_struct && map_struct->cub3d)
            free_cub3d(map_struct->cub3d);
        exit(1);
    }

    /* prefer explicit dimensions from struct, fallback to probing */
    if (map_struct->height > 0)
        rows = (size_t)map_struct->height;
    else
    {
        while (map_struct->map[rows])
            rows++;
    }
    if (map_struct->width > 0)
        max_w = (size_t)map_struct->width;
    else
    {
        for (i = 0; i < rows; ++i)
        {
            size_t l = ft_strlen(map_struct->map[i]);
            if (l > max_w) max_w = l;
        }
    }

    if (rows == 0 || max_w == 0)
    {
        fprintf(stderr, "Error: empty map\n");
        if (map_struct->cub3d) free_cub3d(map_struct->cub3d);
        exit(1);
    }

    /* get start from player if available */
    if (map_struct->player)
    {
        start_x = (int)map_struct->player->pos_col;
        start_y = (int)map_struct->player->pos_row;
    }
    /* fallback: scan map for N/S/E/W */
    if (start_x < 0)
    {
        for (i = 0; i < rows; ++i)
        {
            for (j = 0; j < ft_strlen(map_struct->map[i]); ++j)
            {
                c = map_struct->map[i][j];
                if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                {
                    start_x = (int)j;
                    start_y = (int)i;
                    break;
                }
            }
            if (start_x >= 0) break;
        }
    }

    if (start_x < 0)
    {
        fprintf(stderr, "Error: Missing player start\n");
        if (map_struct->cub3d) free_cub3d(map_struct->cub3d);
        exit(1);
    }

    visited = malloc(sizeof(*visited) * rows);
    if (!visited)
    {
        perror("malloc");
        if (map_struct->cub3d) free_cub3d(map_struct->cub3d);
        exit(1);
    }
    for (i = 0; i < rows; ++i)
    {
        visited[i] = malloc(sizeof(**visited) * max_w);
        if (!visited[i])
        {
            k = 0;
            while (k < i) free(visited[k++]);
            free(visited);
            perror("malloc");
            if (map_struct->cub3d) free_cub3d(map_struct->cub3d);
            exit(1);
        }
        for (j = 0; j < max_w; ++j)
            visited[i][j] = 0;
    }

    start.x = start_x;
    start.y = start_y;
    result = flood_rec(start, (int)rows, map_struct->map, visited);

    for (i = 0; i < rows; ++i) free(visited[i]);
    free(visited);

    if (result)
    {
        fprintf(stderr, "Error: map not closed\n");
        if (map_struct->cub3d) free_cub3d(map_struct->cub3d);
        /* keep original behaviour if you want GNL cleanup: get_next_line(-1); */
        exit(1);
    }
}


