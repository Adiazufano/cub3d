/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:08:32 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:05:08 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	init_flood_filll(t_point *start)
{
	start->rows = 0;
	start->max_w = 0;
	start->start_x = -1;
	start->start_y = -1;
	start->x = 0;
	start->y = 0;
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
