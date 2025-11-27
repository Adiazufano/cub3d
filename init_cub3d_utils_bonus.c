/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:46:23 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:05:20 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_cubed(t_cubed *cub3d)
{
	cub3d->north_texture = NULL;
	cub3d->south_texture = NULL;
	cub3d->west_texture = NULL;
	cub3d->east_texture = NULL;
	cub3d->floor_format = NULL;
	cub3d->sky_format = NULL;
	cub3d->door_texture = "./textures/door.png";
	cub3d->map = NULL;
}

char	*get_line(int fd)
{
	size_t	len;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	return (line);
}

void	add_to_cub3d(int fd, t_cubed *cub3d)
{
	char	*line;
	int		j;

	j = 0;
	line = NULL;
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			empty_line_err(cub3d, fd);
			continue ;
		}
		add_textures(line, cub3d);
		add_formats(line, cub3d);
		add_map(line, cub3d, fd, &j);
		free(line);
	}
}

void	print_cubed(t_cubed *cub3d)
{
	size_t	index;

	index = 0;
	if (cub3d->north_texture)
		printf("%s\n", cub3d->north_texture);
	if (cub3d->south_texture)
		printf("%s\n", cub3d->south_texture);
	if (cub3d->east_texture)
		printf("%s\n", cub3d->east_texture);
	if (cub3d->west_texture)
		printf("%s\n", cub3d->west_texture);
	if (cub3d->floor_format)
		printf("%s\n", cub3d->floor_format);
	if (cub3d->sky_format)
		printf("%s\n", cub3d->sky_format);
	if (!cub3d->map)
		return ;
	while (cub3d->map[index])
	{
		printf("%s\n", cub3d->map[index]);
		index++;
	}
}
