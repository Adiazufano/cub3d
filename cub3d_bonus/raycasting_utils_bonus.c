/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:06:38 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_cube(t_map *m, t_cubed *cub3d)
{
	m->player = malloc (sizeof (t_player));
	if (!m->player)
		return (0);
	m->mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!m->mlx)
	{
		write (2, "Error: Imposible to create MLX\n", 32);
		return (0);
	}
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	if (!m->mlx || !m->image)
	{
		write (2, "Error: Imposible to create the image\n", 38);
		return (0);
	}
	m->key = malloc(sizeof(*(m->key)));
	if (!m->key)
		return (0);
	initialize(m->player, m, cub3d);
	return (1);
}

void	clear_image(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			mlx_put_pixel(m->image, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	paint_image(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (y < (m->height / 2 - m->player->pitch))
				mlx_put_pixel(m->image, x, y, m->cub3d->sky_color);
			else
				mlx_put_pixel(m->image, x, y, m->cub3d->floor_color);
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_map	*m;

	m = (t_map *)param;
	clear_image(m);
	paint_image(m);
	movement(m);
	raycasting(m->player, m);
	paint_minimap(m);
}

void	setup_window(t_map *m)
{
	mlx_image_to_window(m->mlx, m->image, 0, 0);
	mlx_key_hook(m->mlx, key_event, m);
	mlx_loop_hook(m->mlx, game_loop, m);
}
