/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:35:29 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/04 15:46:38 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_program(t_cubed *cub3d, t_map *m, int fd)
{
	print_cubed(cub3d);
	add_to_cub3d(fd, cub3d);
	validate_textures(cub3d);
	validate_formats(cub3d);
	run_flood_check(cub3d);
	normalize_map(cub3d);
	if (!init_cube(m, cub3d))
		return (1);
	m->cub3d = cub3d;
	setup_window(m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	return (1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_cubed	cub3d;
	t_map	m;

	init_cubed(&cub3d);
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
	init_program(&cub3d, &m, fd);
	free(m.player);
	free(m.portal);
	free(m.key);
	free_cub3d(&cub3d);
	close(fd);
	return (0);
}
