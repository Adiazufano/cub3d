/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:23:22 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 18:42:14 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	convert_pixels(mlx_texture_t *tex, uint32_t i)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = tex->pixels [i * 4 + 0];
	g = tex->pixels [i * 4 + 1];
	b = tex->pixels [i * 4 + 2];
	a = tex->pixels [i * 4 + 3];
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

uint32_t	*convert_tex_to_uint(mlx_texture_t *tex)
{
	uint32_t	*pixels;
	uint32_t	i;

	i = 0;
	if (!tex || !tex->pixels || tex->width <= 0 || tex->height <= 0)
		return (NULL);
	pixels = malloc(sizeof(uint32_t) * tex->width * tex->height);
	if (!pixels)
		return (NULL);
	while (i < tex->width * tex->height)
	{
		pixels[i] = convert_pixels(tex, i);
		i++;
	}
	return (pixels);
}

void	load_ene_text(t_anim_ene *e, t_map *m)
{
	mlx_texture_t	*atlas;
	int				total;

	if (!e || !m)
		return ;
	atlas = mlx_load_png ("./textures/Spiderdemon.png");
	if (!atlas)
	{
		printf("Error: fallo al cargar Spiderdemon.png\n");
		exit(1);
	}
	e->atlas = atlas;
	seg_walk (e, m);
	total = e->walk_count;
	if (total <= 0 || total > 1024)
	{
		printf ("Error: total frames inválido (%d)\n", total);
		mlx_delete_texture (e->atlas);
		e->atlas = NULL;
		exit (1);
	}
	init_texture_info (m, total);
	init_texture_enemy (m, e, total);
}
