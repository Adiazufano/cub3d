/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:15:45 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/18 18:24:58 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_or_format(char *p)
{
	if (!p || !p[0])
		return (0);
	if ((p[0] == 'N' && p[1] == 'O')
		|| (p[0] == 'S' && p[1] == 'O')
		|| (p[0] == 'W' && p[1] == 'E')
		|| (p[0] == 'E' && p[1] == 'A')
		|| p[0] == 'F'
		|| p[0] == 'C')
		return (1);
	return (0);
}

int	add_textures_and_formats(char *p, t_cubed *cub3d)
{
	if (cub3d->map_started && is_texture_or_format(p))
		return (-1);
	if (!cub3d->map_started)
	{
		add_textures(p, cub3d);
		add_formats(p, cub3d);
	}
	return (0);
}

void	add_texture_formats_err(char *p, char *line, int fd, t_cubed *cub3d)
{
	if (add_textures_and_formats(p, cub3d) < 0)
	{
		printf("Error: add format or texture after map read\n");
		get_next_line(-1);
		free(line);
		free_cub3d(cub3d);
		close(fd);
		exit(1);
	}
}
