/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:41:24 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/18 17:11:53 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	texture_format(char *path)
{
	unsigned char	buffer[8];
	ssize_t			read_bytes;
	int				fd;

	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
		return (0);
	read_bytes = read(fd, buffer, 8);
	if (read_bytes != 8)
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (buffer[0] != 0x89 || buffer[1] != 'P' || buffer[2] != 'N'
		|| buffer[3] != 'G' || buffer[4] != 0x0D || buffer[5] != 0x0A
		|| buffer[6] != 0x1A || buffer[7] != 0x0A)
		return (0);
	return (1);
}

void	validate_texture_path(char *path, t_cubed *cub3d)
{
	if (!path || !*path)
	{
		printf("Error: missing exture path\n");
		free_exit(cub3d);
	}
	if (!texture_format(path))
	{
		printf("Error: texture is not a PNG file\n");
		free_exit(cub3d);
	}
}

void	check_textures(char *line, t_cubed *cub3d)
{
	char	*path;

	if (line[0] == 'W' && line[1] == 'E')
	{
		path = get_textures_path(line + 2);
		validate_texture_path(path, cub3d);
		free(cub3d -> west_texture);
		cub3d -> west_texture = path;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		path = get_textures_path(line + 2);
		validate_texture_path(path, cub3d);
		free(cub3d -> east_texture);
		cub3d -> east_texture = path;
	}
}

void	add_textures(char *line, t_cubed *cub3d)
{
	char	*path;

	if (line[0] == 'N' && line[1] == 'O')
	{
		path = get_textures_path(line + 2);
		validate_texture_path(path, cub3d);
		free(cub3d -> north_texture);
		cub3d -> north_texture = path;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		path = get_textures_path(line + 2);
		validate_texture_path(path, cub3d);
		free(cub3d -> south_texture);
		cub3d -> south_texture = path;
	}
	check_textures(line, cub3d);
}

char	*get_textures_path(char *s)
{
	char	*p;
	size_t	len;

	p = s;
	while (*p == ' ' || *p == '\t')
		p++;
	len = ft_strlen(p);
	if (len)
	{
		while (len > 0 && (p[len - 1] == ' '
				|| p[len - 1] == '\t' || p[len - 1] == '\n'))
			p[--len] = '\0';
	}
	return (ft_strdup(p));
}
