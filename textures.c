/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:45:19 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/26 16:46:57 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

t_tex_bytes	*load_texture_bytes(const char* path)
{
	mlx_texture_t	*tex;
	t_tex_bytes		*t;
	size_t size;

	tex = mlx_load_png(path);
	if (!tex || !tex->pixels)
	{
		mlx_delete_texture(tex);
		return (NULL);
	}
	t = malloc(sizeof(t_tex_bytes));
	t->width = (int)tex->width;
	t->height = (int)tex->height;
	t->channels = tex->bytes_per_pixel;
	size = (size_t)t->width * (size_t)t->height * (size_t)t->channels;
	t->pixels = malloc(size);
	if (!t || !t->pixels)
	{
		mlx_delete_texture(tex);
		free(t);
		return (NULL);
	}
	ft_memcpy(t->pixels, tex->pixels, size);
	mlx_delete_texture(tex);
	return (t);
}

int	get_text_x(t_draw_col *p, int texW)
{
	int	tx;

	tx = (int)(p->wallX * (double)texW);
	if (tx < 0)
		return(0);
	if (tx >= texW)
		return (texW - 1);
	if ((p->side == 0 && p->rayDirX > 0)
		|| (p->side == 1 && p->rayDirY < 0))
		return (texW - tx - 1);
	return (tx);
}

void	put_tex_pixel(t_draw_col *p, t_tex_ctx *c, int64_t texpos, int y)
{
	int	texY;
	uint8_t	*src;
	uint8_t	*dst;

	texY = (int)(texpos >> 16);
	if (texY < 0)
		texY = 0;
	if (texY >= c->texH)
		texY = c->texH - 1;
	src = &p->tex->pixels[(texY * c->texW +  c->texX) *  c->channels];
	if (c->channels == 4 && src[3] == 0)
		return;
	dst = &p->screen[y *  c->fb_stride + p->x * 4];
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	if (c->channels == 4)
		dst[3]=src[3];
	else
		dst[3] = 255;
}

void	draw_column_loop(t_draw_col *p, t_tex_ctx *c, int64_t texpos)
{
	int	y;

	y = p->drawStart;
	while (y <= p->drawEnd)
	{
		if (y < 0 || y >= p->screen_h)
		{
			texpos += c->step;
			y++;
			continue;
		}
		put_tex_pixel(p, c, texpos, y);
		texpos += c->step;
		y++;
	}
}


void	draw_textured_column_no_pack(t_draw_col *p)
{
	t_tex_ctx c;
	int64_t	texpos;

	if (!p || !p->screen || !p->tex || p->lineHeight <= 0)
		return;
	c.texW = p->tex->width;
	c.texH = p->tex->height;
	c.channels = p->tex->channels;
	c.texX = get_text_x(p, c.texW);
	c.step = ((int64_t)c.texH << 16) / (int64_t)p->lineHeight;
	texpos = ((int64_t)((p->drawStart +  p->pitch) - (p->screen_h / 2)
				+ (p->lineHeight / 2))) * c.step;
	c.fb_stride = p->screen_w * 4;
	draw_column_loop(p, &c, texpos);
}
