/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:42:28 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:06:08 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_height(t_map *m)
{
	int	row;

	row = 0;
	while (m->map[row])
		row++;
	return (row);
}

int	get_width(t_map *m)
{
	int	row;
	int	max;
	int	len;

	row = 0;
	max = 0;
	while (m->map[row])
	{
		len = 0;
		while (m -> map[row][len])
			len++;
		if (len > max)
			max = len;
		row++;
	}
	return (max);
}

void	paint_minimap_3(t_map *m, int x, int y, int a)
{
	int	b;

	while (a < (x * 6) + 6)
	{
		b = y * 6;
		while (b < (y * 6) + 6)
		{
			mlx_put_pixel(m->image, a, b, 0x0000FFFF);
			b++;
		}
		a++;
	}
}

void	paint_minimap_1(t_map *m, int x, int y, int a)
{
	int	b;

	while (a < (x * 6) + 6)
	{
		b = y * 6;
		while (b < (y * 6) + 6)
		{
			mlx_put_pixel(m->image, a, b, 0x00FF0FFF);
			b++;
		}
		a++;
	}
}

void	paint_minimap_0(t_map *m, int x, int y, int a)
{
	int	b;

	while (a < (x * 6) + 6)
	{
		b = y * 6;
		while (b < (y * 6) + 6)
		{
			mlx_put_pixel(m->image, a, b, 0xF0F0F0FF);
			b++;
		}
		a++;
	}
}
