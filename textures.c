/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:45:19 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/27 11:06:03 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex_bytes	*load_texture_bytes(const char *path)
{
	mlx_texture_t	*tex;
	t_tex_bytes		*t;
	size_t			size;

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

int	get_text_x(t_draw_col *p, int tex_w)
{
	int	tx;

	tx = (int)(p->wallx * (double)tex_w);
	if (tx < 0)
		return (0);
	if (tx >= tex_w)
		return (tex_w - 1);
	if ((p->side == 0 && p->ray_dir_x > 0)
		|| (p->side == 1 && p->ray_dir_y < 0))
		return (tex_w - tx - 1);
	return (tx);
}

void	put_tex_pixel(t_draw_col *p, t_tex_ctx *c, int64_t texpos, int y)
{
	uint8_t	*src;
	uint8_t	*dst;
	int		tex_y;

	tex_y = (int)(texpos >> 16);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= c->tex_h)
		tex_y = c->tex_h - 1;
	src = &p->tex->pixels[(tex_y * c->tex_w + c->tex_x) * c->channels];
	if (c->channels == 4 && src[3] == 0)
		return ;
	dst = &p->screen[y * c->fb_stride + p->x * 4];
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	if (c->channels == 4)
		dst[3] = src[3];
	else
		dst[3] = 255;
}

void	draw_column_loop(t_draw_col *p, t_tex_ctx *c, int64_t texpos)
{
	int	y;

	y = p->draw_start;
	while (y <= p->draw_end)
	{
		if (y < 0 || y >= p->screen_h)
		{
			texpos += c->step;
			y++;
			continue ;
		}
		put_tex_pixel(p, c, texpos, y);
		texpos += c->step;
		y++;
	}
}

void	draw_textured_column_no_pack(t_draw_col *p)
{
	t_tex_ctx	c;
	int64_t		texpos;

	if (!p || !p->screen || !p->tex || p->line_height <= 0)
		return ;
	c.tex_w = p->tex->width;
	c.tex_h = p->tex->height;
	c.channels = p->tex->channels;
	c.tex_x = get_text_x(p, c.tex_w);
	c.step = ((int64_t)c.tex_h << 16) / (int64_t)p->line_height;
	texpos = ((int64_t)((p->draw_start + p->pitch) - (p->screen_h / 2)
				+ (p->line_height / 2))) * c.step;
	c.fb_stride = p->screen_w * 4;
	draw_column_loop(p, &c, texpos);
}
