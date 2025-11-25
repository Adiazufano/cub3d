/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:06:29 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/25 15:45:00 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
void	paint_minimap_map(t_map *m)
{
	int	x;
	int	y;
	int	a;
	int	width;
	int	height;
	char c;

	y = 0;
	width = get_width(m);
	height = get_height(m);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			a = x * 6;
			if (m->map[y])
			{
				if (m->map[y][x] != '\0')
					c = m->map[y][x];
				else
					c = ' ';
			}
			else
				c = ' ';
			if (c == '1')
				paint_minimap_1(m, x, y, a);
			else if (c == '3')
				paint_minimap_3(m, x, y, a);
			else if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
				paint_minimap_0(m, x, y, a);
			x++;
		}
		y++;
	}
	paint_minimap_player(m);
}

void	paint_minimap(t_map *m)
{
    int	width;
    int	height;

    if (!m)
        return ;
    width = get_width(m);
    height = get_height(m);
    paint_minimap_map(m);
}
