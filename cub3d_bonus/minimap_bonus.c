/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:06:29 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/04 11:03:30 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	paint_minimap_c(t_map *m, int x, int y)
{
	char	c;
	int		a;

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
	else if (c == '3' || c == '4')
		paint_minimap_3(m, x, y, a);
	else if (c == '0' || c == '2' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		paint_minimap_0(m, x, y, a);
}

void	paint_minimap_map(t_map *m)
{
	int	x;
	int	y;
	int	width;
	int	height;

	y = 0;
	width = get_width(m);
	height = get_height(m);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			paint_minimap_c(m, x, y);
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
