/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:35:29 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/19 10:59:48 by aldiaz-u         ###   ########.fr       */
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
/*DEBUG: print values of cub3d*/
void	print_cub3d(t_cubed *cub3d)
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

int	add_map_line(t_cubed **cub3d, const char *line)
{
	size_t	n;
	char	**new_map;
	char	*dup;
	size_t	index;

	index = 0;
	n = 0;
	if (!line)
		return (0);
	dup = ft_strdup(line);
	if (!dup)
		return (-1);
	while ((*cub3d)->map && (*cub3d)->map[n])
		n++;
	new_map = malloc(sizeof *new_map * (n + 2));
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
	return (0);
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

char	*get_textures_path(char *s)
{
	char 	*p;
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

void	add_formats(char *line, t_cubed *cub3d)
{
	if (line[0] == 'F')
	{
		free(cub3d -> floor_format);
		cub3d -> floor_format = ft_strdup(line + 1);
	}
	else if (line[0] == 'C')
	{
		free(cub3d -> sky_format);
		cub3d -> sky_format = ft_strdup(line + 1);
	}
}

void	map_err(char *line, int *j, t_cubed *cub3d, int fd)
{
	
	if ((line[*j] != ' ' && line[*j] != '1'
		&& line[*j] != '0' && line[*j] != 'N' && line[*j] != 'S'
		&& line[*j] != 'E' && line[*j] != 'W') || line[*j] == '\t')
	{
		printf("Error: format error\n");
		get_next_line(-1);
		free(line);
		free_cub3d(cub3d);
		close(fd);
		exit(1);
	}
}

void	add_map(char *line, t_cubed *cub3d, int fd, int *j)
{
	if (line[0] == ' ' || line[0] == '\t' || line[0] == '1'
		|| line[0] == '\0')
	{
		*j = 0;
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

void	validate_texture_path(char *path, t_cubed *cub3d)
{
	int		fd;
	char 	buf;
	size_t 	r;

	if (!path || !*path)
	{
		printf("Error: missing exture path\n");
		free_cub3d(cub3d);
		exit(1);
	}
	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror ("Error opening texture");
		free_cub3d(cub3d);
		exit(1);
	}
	r = read(fd, &buf, 1);
	if (r <= 0)
	{
		close(fd);
		printf("Error: invalid texture file\n");
		free_cub3d(cub3d);
		exit(1);
	}
	close(fd);
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

int	count_commas(t_cubed *cub3d, char *format)
{
	int	index;
	int	j;
	int	commas;

	index = 0;
	j = 0;
	commas = 0;
	while (format[index])
	{
		if (format[index] == ',')
		{
			commas++;
			j = index + 1;
			while (format[j] == ' ' || format[j] == '\t')
				j++;
			if (format[j] == ',' || format[j] == '\0')
			{
				printf("Error: invalid rgb format\n");
				free_cub3d(cub3d);
				exit(1);
			}
		}
		index++;
	}
	return (commas);
}

void	validate_commas(char *format, t_cubed *cub3d)
{
	int	index;
	int	commas;

	index = 0;
	while (format[index] == ' '  || format[index] == '\t')
		index++;
	if (format[index] == ',' || format[index] == '\0')
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
	commas = count_commas(cub3d, format);
	if (commas != 2)
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
}

void	split_size(char **split, t_cubed *cub3d)
{
	int	index;

	index = 0;
	while (split[index])
		index++;
	if (index != 3)
	{
		free_split(split);
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
}

void	split_isdigit(char **split, t_cubed *cub3d)
{
	int	index;
	int	j;

	index = 0;
	while (split[index])
	{
		j = 0;
		while (split[index][j])
		{
			while (split[index][j] == ' ' || split[index][j] == '\t')
				j++;
			if  (!ft_isdigit(split[index][j]))
			{
				free_split(split);
				printf("Error: invalid rgb format\n");
				free_cub3d(cub3d);
				exit(1);
			}
			j++;
		}
		index++;
	}
}
void	validate_rgb(t_cubed *cub3d, char *format)
{
	int		r;
	int		g;
	int		b;
	char	**splited_format;

	validate_commas(format, cub3d);
	splited_format = ft_split(format, ',');
	split_size(splited_format, cub3d);
	split_isdigit(splited_format, cub3d);
	r = ft_atoi(splited_format[0]);
	g = ft_atoi(splited_format[1]);
	b = ft_atoi(splited_format[2]);
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
}

void	validate_formats(t_cubed *cub3d)
{
	validate_rgb(cub3d, cub3d -> floor_format);
	validate_rgb(cub3d, cub3d -> sky_format);
}

void	validate_textures(t_cubed *cub3d)
{
	validate_texture_path(cub3d -> north_texture, cub3d);
	validate_texture_path(cub3d -> south_texture, cub3d);
	validate_texture_path(cub3d -> east_texture, cub3d);
	validate_texture_path(cub3d -> west_texture, cub3d);
}

void	add_to_cub3d(int fd, t_cubed *cub3d)
{
	int		i;
	int		j;
	char	*line;

	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (line[i])
			i++;
		if (i > 0 && line[i - 1] == '\n')
			line[i - 1] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			empty_line_err(cub3d, fd);
			continue;
		}
		i = 0;
		add_textures(line, cub3d);
		add_formats(line, cub3d);
		add_map(line, cub3d, fd, &j);
		free(line);
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_cubed	cub3d;
	t_map	m;

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
	add_to_cub3d(fd, &cub3d);
	validate_textures(&cub3d);
	validate_formats(&cub3d);
	run_flood_check(&cub3d);
	if(!init_cube(&m, &cub3d))
	return(1);
	setup_window(&m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	free(m.player);   
	free_cub3d(&cub3d);
	close(fd);
	return (0);
}

