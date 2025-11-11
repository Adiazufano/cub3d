/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:35:29 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/11 13:29:23 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cubed *cub3d)
{
	cub3d->north_texture = NULL;
	cub3d->south_texture = NULL;
	cub3d->west_texture = NULL;
	cub3d->east_texture = NULL;
	cub3d->floor_format = NULL;
	cub3d->sky_format = NULL;
	cub3d->map = NULL;
}

void	free_cub3d(t_cubed *cub3d)
{
	free(cub3d->north_texture);
	free(cub3d->south_texture);
	free(cub3d->east_texture);
	free(cub3d->west_texture);
	free(cub3d->floor_format);
	free(cub3d->sky_format);
	free(cub3d->map);
}
/*DEBUG: print values of cub3d*/
void	print_cub3d(t_cubed *cub3d)
{
	printf("%s\n", cub3d->north_texture);
	printf("%s\n", cub3d->south_texture);
	printf("%s\n", cub3d->east_texture);
	printf("%s\n", cub3d->west_texture);
	printf("%s\n", cub3d->floor_format);
	printf("%s\n", cub3d->sky_format);
}
int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	t_cubed	cub3d;
	int		i;
	char	*p;
	int		j;

	init_cub3d(&cub3d);
	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		printf("Invalid format Error\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error:");
		exit(1);
	}
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (line[i])
			i++;
		if (i > 0 && line[i - 1] == '\n')
			line[i - 1] = '\0';
		i = 0;
		if (line[0] == 'N' && line[1] == 'O')
		{
			free(cub3d.north_texture);
			p = line + 2;
			while (*p == ' ' || *p == '\t')
				p++;
			cub3d.north_texture = ft_strdup(p);
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			free(cub3d.south_texture);
			p = line + 2;
			while (*p == ' ' || *p == '\t')
				p++;
			cub3d.south_texture = ft_strdup(p);
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			free(cub3d.west_texture);
			p = line + 2;
			while (*p == ' ' || *p == '\t')
				p++;
			cub3d.west_texture = ft_strdup(p);
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			free(cub3d.east_texture);
			p = line + 2;
			while (*p == ' ' || *p == '\t')
				p++;
			cub3d.east_texture = ft_strdup(p);
		}
		else if (line[0] == 'F')
		{
			free(cub3d.floor_format);
			cub3d.floor_format = ft_strdup(line + 1);
		}
		else if (line[0] == 'C')
		{
			free(cub3d.sky_format);
			cub3d.sky_format = ft_strdup(line + 1);
		}
		else if (line[0] == ' ' || line[0] == '\t' || line[0] == '1' || line[0] == '\0')
		{
			j = 0;
			while (line[j])
			{
				if (line[j] != ' ' && line[j] != '\t' && line[j] != '1' && line[j] != '0'
					&& line[j] != 'N' && line[j] != 'S' && line[j] != 'E'
					&& line[j] != 'W')
				{
					printf("Error: format error\n");
					exit(1);
				}
				j++;
			}
		}
		free(line);
	}
	print_cub3d(&cub3d);
	close(fd);
	free_cub3d(&cub3d);
	return (0);
}
