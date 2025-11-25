/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:06:29 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/25 09:28:25 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  FUNCIÓN PARA PINTAR LAS CASILLAS DE MUROS EN EL MINIMAPA  */

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

/*  FUNCIÓN PARA PINTAR LAS CASILLAS VACÍAS EN EL MINIMAPA  */

void	paint_minimap_0(t_map *m, int x, int y, int a)
{
	int	b;

	b = 0;
	while (a < (x * 6) + 6)
	{
		b = y * 6;
		while (b < (y * 6) + 6)
		{
			mlx_put_pixel(m->image, a, b, 0xf0f0f0FF);
			b++;
		}
		a++;
	}
}

void	paint_minimap_player(t_map *m)
{
	t_player	*p;
	int			pos_x;
	int			pos_y;
	int			a;
	int			b;

	p = m->player;
	pos_x = p->pos_col * 6;
	pos_y = p->pos_row * 6;
	a = pos_x;
	while (a < (pos_x + 6))
	{
		b = pos_y;
		while (b < (pos_y + 6))
		{
			mlx_put_pixel(m->image, a, b, 0xFF0000FF);
			b++;
		}
		a++;
	}
}

void	paint_minimap_map(t_map *m)
{
	int	x;
	int	y;
	int	a;

	y = 0;
	while (y < mapwidth)
	{
		x = 0;
		while (x < mapheight)
		{
			a = x * 6;
			if (m->map[y][x] == 1 || m->map[y][x] == 3)
				paint_minimap_1(m, x, y, a);
			else
				paint_minimap_0(m, x, y, a);
			x++;
		}
		y++;
	}
	paint_minimap_player(m);
}

void	paint_minimap(t_map *m)
{
	t_player	*p;
	int			pos_x;
	int			pos_y;

	p = m->player;
	pos_x = p->pos_row;
	pos_y = p->pos_col;
	paint_minimap_map(m);
}
