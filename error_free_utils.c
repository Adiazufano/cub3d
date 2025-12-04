/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:37:15 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/04 15:45:20 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_err(char *line, int *j, t_cubed *cub3d, int fd)
{
	if (line[*j] != ' ' && line[*j] != '1'
		&& line[*j] != '0' && line[*j] != 'N' && line[*j] != 'S'
		&& line[*j] != 'E' && line[*j] != 'W' && line[*j] != '\t')
	{
		printf("Error: format error\n");
		get_next_line(-1);
		free(line);
		free_cub3d(cub3d);
		close(fd);
		exit(1);
	}
}

void	empty_line_err(t_cubed *cub3d, int fd)
{
	if (cub3d -> map)
	{
		printf("Error: empty line inside map\n");
		get_next_line(-1);
		free_cub3d(cub3d);
		close(fd);
		exit(1);
	}
}

void	free_split(char **split)
{
	int	index;

	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}

void	free_exit(t_cubed *cub3d)
{
	free_cub3d(cub3d);
	exit(1);
}

void	free_cub3d(t_cubed *cub3d)
{
	size_t	index;

	index = 0;
	free(cub3d->north_texture);
	free(cub3d->south_texture);
	free(cub3d->east_texture);
	free(cub3d->west_texture);
	free(cub3d->floor_format);
	free(cub3d->sky_format);
	if (cub3d->map)
	{
		while (cub3d->map[index])
		{
			free(cub3d->map[index]);
			index++;
		}
		free(cub3d->map);
		cub3d->map = NULL;
	}
}
