/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:16:04 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:21:34 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
