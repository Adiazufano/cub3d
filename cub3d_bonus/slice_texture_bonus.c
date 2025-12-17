/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:55:19 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 18:40:05 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_slice_texture(mlx_texture_t *out, t_map *m, int x, int y)
{
	out->width = FRAMEW;
	out->height = FRAMEH;
	out->bytes_per_pixel = 4;
	out->pixels = malloc(FRAMEW * FRAMEH * 4);
	if (!out->pixels)
	{
		free(out);
		return ;
	}
	m->helper->row = 0;
	m->helper->col = 0;
	m->helper->var1 = x;
	m->helper->var2 = y;
}

void	slice_texture_helper(mlx_texture_t *out, mlx_texture_t *atlas, t_map *m)
{
	m->helper->dest = (m->helper->row * FRAMEW + m->helper->col) * 4;
	m->helper->src = ((m->helper->row + m->helper->var2) * atlas->width
			+ (m->helper->col + m->helper->var1)) * 4;
	out->pixels[m->helper->dest + 0] = atlas->pixels[m->helper->src + 0];
	out->pixels[m->helper->dest + 1] = atlas->pixels[m->helper->src + 1];
	out->pixels[m->helper->dest + 2] = atlas->pixels[m->helper->src + 2];
	out->pixels[m->helper->dest + 3] = atlas->pixels[m->helper->src + 3];
	m->helper->col++;
}

mlx_texture_t	*slice_texture(mlx_texture_t *atlas, t_map *m, int x, int y)
{
	mlx_texture_t	*out;

	out = malloc(sizeof(mlx_texture_t));
	if (!out)
		return (NULL);
	if (!atlas || m->helper->var1 < 0 || m->helper->var2 < 0
		|| FRAMEW <= 0 || FRAMEH <= 0)
		return (NULL);
	if ((uint32_t)(x + FRAMEW) > atlas->width ||
		(uint32_t)(y + FRAMEH) > atlas->height)
	{
		printf("Error: slice fuera de los límites del atlas\n");
		return (NULL);
	}
	init_slice_texture(out, m, x, y);
	while (m->helper->row < FRAMEH)
	{
		m->helper->col = 0;
		while (m->helper->col < FRAMEW)
			slice_texture_helper(out, atlas, m);
		m->helper->row++;
	}
	return (out);
}

void	seg_walk(t_anim_ene *e, t_map *m)
{
	int	i;

	i = 0;
	e->walk_count = 6;
	e->walk[0] = slice_texture(e->atlas, m, 0, 45);
	e->walk[1] = slice_texture(e->atlas, m, 287, 45);
	e->walk[2] = slice_texture(e->atlas, m, 546, 45);
	e->walk[3] = slice_texture(e->atlas, m, 821, 45);
	e->walk[4] = slice_texture(e->atlas, m, 1092, 45);
	e->walk[5] = slice_texture(e->atlas, m, 1365, 45);
	while (i < e->walk_count)
	{
		if (!e->walk[i])
			printf("Warning: seg_walk slice %d == NULL\n", i);
		i++;
	}
}
