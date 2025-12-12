/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:23:22 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 17:25:39 by mparra-s         ###   ########.fr       */
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
		return NULL;
	pixels = malloc(sizeof(uint32_t) * tex->width * tex->height);
	if (!pixels)
		return NULL;

	while (i < tex->width * tex->height)
	{

		pixels[i] = convert_pixels(tex, i);
		i++;
	}
	return pixels;
}

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
void slice_texture_helper(mlx_texture_t *out, mlx_texture_t *atlas, t_map *m)
{
	m->helper->dest = (m->helper->row * FRAMEW + m->helper->col) * 4;
	m->helper->src = ((m->helper->row + m->helper->var2) * atlas->width + (m->helper->col + m->helper->var1)) * 4;
	out->pixels[m->helper->dest + 0] = atlas->pixels[m->helper->src + 0];
	out->pixels[m->helper->dest + 1] = atlas->pixels[m->helper->src + 1];
	out->pixels[m->helper->dest + 2] = atlas->pixels[m->helper->src + 2];
	out->pixels[m->helper->dest + 3] = atlas->pixels[m->helper->src + 3];
	m->helper->col++;    
}
mlx_texture_t *slice_texture(mlx_texture_t *atlas, t_map *m, int x, int y)
{
	mlx_texture_t *out;
	
	out = malloc(sizeof(mlx_texture_t));
	if (!out)
		return NULL;
	if (!atlas || m->helper->var1 < 0 || m->helper->var2 < 0 || FRAMEW <= 0 || FRAMEH <= 0)
		return NULL;
	if ((uint32_t)(x + FRAMEW) > atlas->width ||
		(uint32_t)(y + FRAMEH) > atlas->height)
	{
		printf("Error: slice fuera de los límites del atlas\n");
		return NULL;
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


/******************************************************************************/
/*    Función donde vamos a cargar el atlas png con todos los sprites         */
/*    del enemigo y vamos a llamar a la función que va a seccionar cada uno   */
/******************************************************************************/

void    seg_walk(t_anim_ene *e, t_map *m)
{
	int i;

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

void    tex_id(int *src, int count, int *idx)
{
	int i;

	i = 0;
	while (i < count)
	{
		src[i] =  *idx;
		i++;
		(*idx)++;
	}
	
}

void push_text_aux(t_tex_info *dst, mlx_texture_t **src, int count, int capacity)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (!src[i])
		{
			printf("push_text_safe: slice src[%d] == NULL, se omite\n", i);
			continue ;
		}
		if (dst->count < 0 || dst->count >= capacity)
		{
			printf("push_text_safe: warning - dst->count (%d) fuera de capacidad (%d)\n",
				   dst->count, capacity);
			break ;
		}
		dst->widths[dst->count] = src[i]->width;
		dst->heights[dst->count] = src[i]->height;
		dst->pixeles[dst->count] = convert_tex_to_uint(src[i]);
		if (!dst->pixeles[dst->count])
			exit(1);
		i++;
		dst->count++;
	}
} 

void push_text(t_tex_info *dst, mlx_texture_t **src, int count, int capacity)
{
	if (!dst || !src || count <= 0 || capacity <= 0)
	{
		printf("push_text_safe: puntero NULL o count/capacity inválidos\n");
		return ;
	}
	push_text_aux(dst, src, count, capacity);
}

void init_texture_info(t_map *m, int total)
{
	int i;

	i = 1;
	m->texture_info = malloc(sizeof(t_tex_info));
	if (!m->texture_info) exit(1);
	ft_memset(m->texture_info, 0, sizeof(t_tex_info));
	m->texture_info->pixeles = malloc(sizeof(uint32_t*) * total);
	m->texture_info->widths  = malloc(sizeof(int) * total);
	m->texture_info->heights = malloc(sizeof(int) * total);
	if (!m->texture_info->pixeles || !m->texture_info->widths || !m->texture_info->heights)
	{
		perror("malloc");
		exit(1);
	}
	while (i < total)
	{
		m->texture_info->pixeles[i] = NULL;
		m->texture_info->widths[i] = 0;
		m->texture_info->heights[i] = 0;
		i++;
	}
	m->texture_info->count = 0;    
}
void init_texture_enemy(t_map *m, t_anim_ene *e, int total)
{
	int idx;
	
	idx = 0;
	m->texture_enemy = malloc(sizeof(t_enemy_tex_info));
	if (!m->texture_enemy)
		exit(1);
	m->texture_enemy->walk = e->walk;
	m->texture_enemy->walk_count = e->walk_count;
	push_text(m->texture_info, e->walk, e->walk_count, total);
	m->n_sprites = m->texture_info->count;
	tex_id(e->walk_tex_id, e->walk_count, &idx);
	mlx_delete_texture(e->atlas);
	e->atlas = NULL;
	m->tex_width = FRAMEW;
	m->tex_height = FRAMEH;    
}

void load_ene_text(t_anim_ene *e, t_map *m)
{
	mlx_texture_t   *atlas;
	int             total;
	if (!e || !m)
		return;
	atlas = mlx_load_png("./textures/Spiderdemon.png");
	if (!atlas)
	{
		printf("Error: fallo al cargar Spiderdemon.png\n");
		exit(1);
	}
	e->atlas = atlas;
	seg_walk(e, m);
	total = e->walk_count;
	if (total <= 0 || total > 1024)
	{
		printf("Error: total frames inválido (%d)\n", total);
		mlx_delete_texture(e->atlas);
		e->atlas = NULL;
		exit(1);
	}
	init_texture_info(m, total);
	init_texture_enemy(m, e, total);
}

