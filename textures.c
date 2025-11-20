/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:45:19 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/20 15:54:57 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex_bytes	*load_texture_bytes(const char* path)
{
	mlx_texture_t	*tex;
	t_tex_bytes		*t;
	
	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	if (!tex->pixels)
	{
		mlx_delete_texture(tex);
		return (NULL);
	}
	t = malloc(sizeof(t_tex_bytes));
	if (!t)
	{
		mlx_delete_texture(tex);
		return (NULL);
	}
	t->width = (int)tex->width;
	t->height = (int)tex->height;
	t->channels = tex->bytes_per_pixel;
	t->pixels = (uint8_t *)tex->pixels;
	return (t);
}

void	draw_textured_column_no_pack(
	uint8_t *screen, int screen_w, int screen_h,
	int x, int drawStart, int drawEnd, int lineHeight,
	t_tex_bytes *tex, double wallX, int side, double rayDirX, double rayDirY)
{
	int	texW;
	int	texH;
	int	texX;
	int	channels;
	int64_t	step;
	int64_t	texpos;
	int	fb_stride;
	int	y;
	int	texY;
	uint8_t	*src;
	uint8_t	*dst;

	if (!screen || !tex || lineHeight <= 0)
		return;
	texW = tex->width;
	texH = tex->height;
	channels = tex->channels;
	texX = (int)(wallX * (double)texW);
	if (tex < 0)
		texX = 0;
	if (texX >= texW)
		texX = texW - 1;
	if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		texX = texW - texX - 1;
	step = ((int64_t)texH << 16) / (int64_t)lineHeight;
	texpos = ((int64_t)(drawStart - (screen_h / 2) + (lineHeight / 2))) * step;
	fb_stride = screen_w * 4;
	y = drawStart;
	while (y <= drawEnd)
	{
		if (y < 0 || y >= screen_h)
		{
			texpos += step;
			continue;
		}
		texY = (int)(texpos >> 16);
		if (texY < 0)
			texY = 0;
		if (texY >= texH)
			texY = texH - 1;
		src = &tex->pixels[(texY * texW + texX) * channels];
		dst = &screen[y *fb_stride + x * 4];
		if (channels == 4)
		{
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
		else
		{
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = 255;
		}
		texpos += step;
		y++;
	}
}