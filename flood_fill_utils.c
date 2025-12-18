/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:08:32 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/18 14:36:17 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	alloc_visited(int ***visited, t_point *start, t_cubed *cub3d)
{
	int		i;
	size_t	rows;
	size_t	rowlen;

	if (!visited || !start || !cub3d || !cub3d->map)
		return (-1);
	rows = start->rows;
	*visited = malloc(rows * sizeof(int *));
	if (!*visited)
		return (-1);
	i = 0;
	while ((size_t)i < rows)
	{
		rowlen = ft_strlen(cub3d->map[i]);
		(*visited)[i] = ft_calloc(rowlen, sizeof(int));
		if (!(*visited)[i])
		{
			while (--i >= 0)
				free((*visited)[i]);
			free(*visited);
			return (-1);
		}
		i++;
	}
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
	if (start->rows >= 256 || start->max_w >= 256)
	{
		printf("Error: map too big\n");
		free_cub3d(cub3d);
		exit(1);
	}
	if (start->rows <= 0 || start->max_w <= 0)
	{
		printf("Error: empty map\n");
		free_cub3d(cub3d);
		exit(1);
	}
}
