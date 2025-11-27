/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:41:24 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 09:07:29 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_texture_path(char *path, t_cubed *cub3d)
{
	char	buf;
	int		fd;
	size_t	r;

	if (!path || !*path)
	{
		printf("Error: missing exture path\n");
		free_exit(cub3d);
	}
	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror ("Error opening texture");
		free_exit(cub3d);
	}
	r = read(fd, &buf, 1);
	if (r <= 0)
	{
		close(fd);
		printf("Error: invalid texture file\n");
		free_exit(cub3d);
	}
	close(fd);
}

void	add_textures(char *line, t_cubed *cub3d)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		free(cub3d -> north_texture);
		cub3d -> north_texture = get_textures_path(line + 2);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		free(cub3d -> south_texture);
		cub3d -> south_texture = get_textures_path(line + 2);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		free(cub3d -> west_texture);
		cub3d -> west_texture = get_textures_path(line + 2);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		free(cub3d -> east_texture);
		cub3d -> east_texture = get_textures_path(line + 2);
	}
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
		while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
			p[--len] = '\0';
	}
	return (ft_strdup(p));
}
