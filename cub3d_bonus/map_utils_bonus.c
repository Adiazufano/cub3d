/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:34:39 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/18 15:46:26 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	add_new_map(t_cubed **cub3d, char *dup, size_t n)
{
	size_t	index;
	char	**new_map;

	index = 0;
	new_map = malloc (sizeof * new_map * (n + 2));
	if (!new_map)
	{
		free(dup);
		return (-1);
	}
	while (index < n)
	{
		new_map[index] = (*cub3d)->map[index];
		index++;
	}
	new_map[n] = dup;
	new_map[n + 1] = NULL;
	free((*cub3d)->map);
	(*cub3d)->map = new_map;
	return (1);
}

int	add_map_line(t_cubed **cub3d, const char *line)
{
	size_t	n;
	char	*dup;
	size_t	len;

	n = 0;
	if (!line)
		return (0);
	dup = ft_strdup(line);
	if (!dup)
		return (-1);
	len = ft_strlen(dup);
	if (len > 0 && dup[len - 1] == '\r')
		dup[len - 1] = '\0';
	while ((*cub3d)->map && (*cub3d)->map[n])
		n++;
	add_new_map(cub3d, dup, n);
	return (0);
}

void	add_map(char *line, t_cubed *cub3d, int fd, int *j)
{
	if (line[0] == ' ' || line[0] == '\t' || line[0] == '1'
		|| line[0] == '0' || line[0] == '\0')
	{
		*j = 0;
		cub3d->map_started = 1;
		while (line[*j])
		{
			map_err(line, j, cub3d, fd);
			(*j)++;
		}
		if (add_map_line(&cub3d, line) < 0)
		{
			perror("malloc");
			free(line);
			free_cub3d(cub3d);
			close(fd);
			exit(1);
		}
	}
}

void	normalize_map_h(t_cubed *cub3d, size_t w, size_t maxw, size_t i)
{
	char	*buf;

	w = ft_strlen(cub3d->map[i]);
	if (w < maxw)
	{
		buf = malloc(maxw + 1);
		if (!buf)
		{
			perror("malloc");
			free_cub3d(cub3d);
			exit(1);
		}
		ft_memcpy(buf, cub3d->map[i], w);
		ft_memset(buf + w, ' ', maxw - w);
		buf[maxw] = '\0';
		free(cub3d->map[i]);
		cub3d->map[i] = buf;
	}
}

void	normalize_map(t_cubed *cub3d)
{
	size_t	i;
	size_t	height;
	size_t	maxw;
	size_t	w;

	if (!cub3d || !cub3d->map)
		return ;
	height = 0;
	maxw = 0;
	while (cub3d->map[height])
	{
		w = ft_strlen(cub3d->map[height]);
		if (w > maxw)
			maxw = w;
		height++;
	}
	if (maxw == 0)
		return ;
	i = 0;
	while (i < height)
	{
		normalize_map_h(cub3d, w, maxw, i);
		i++;
	}
}
