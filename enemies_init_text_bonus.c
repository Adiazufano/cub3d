/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_init_text_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:58:42 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 18:11:29 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	tex_id(int *src, int count, int *idx)
{
	int	i;

	i = 0;
	while (i < count)
	{
		src[i] = *idx;
		i++;
		(*idx)++;
	}
}

void	push_text(t_tex_info *dst, mlx_texture_t **src, int count, int capacity)
{
	if (!dst || !src || count <= 0 || capacity <= 0)
	{
		printf("push_text_safe: puntero NULL o count/capacity inválidos\n");
		return ;
	}
	push_text_aux(dst, src, count, capacity);
}

void	init_texture_info(t_map *m, int total)
{
	int	i;

	i = 1;
	m->texture_info = malloc(sizeof(t_tex_info));
	if (!m->texture_info)
		exit(1);
	ft_memset(m->texture_info, 0, sizeof(t_tex_info));
	m->texture_info->pixeles = malloc (sizeof (uint32_t *) * total);
	m->texture_info->widths = malloc (sizeof (int) * total);
	m->texture_info->heights = malloc (sizeof (int) * total);
	if (!m->texture_info->pixeles || !m->texture_info->widths
		|| !m->texture_info->heights)
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

void	push_text_aux(t_tex_info *dst, mlx_texture_t **src,
		int count, int capacity)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!src[i])
		{
			printf("push_text_safe: slice src[%d] == NULL\n", i);
			continue ;
		}
		if (dst->count < 0 || dst->count >= capacity)
		{
			printf("push_text_safe: warning - dst->count (%d) out"
				"of capacity (%d)\n", dst->count, capacity);
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

void	init_texture_enemy(t_map *m, t_anim_ene *e, int total)
{
	int	idx;

	idx = 0;
	m->texture_enemy = malloc (sizeof(t_enemy_tex_info));
	if (!m->texture_enemy)
		exit (1);
	m->texture_enemy->walk = e->walk;
	m->texture_enemy->walk_count = e->walk_count;
	push_text (m->texture_info, e->walk, e->walk_count, total);
	m->n_sprites = m->texture_info->count;
	tex_id (e->walk_tex_id, e->walk_count, &idx);
	mlx_delete_texture (e->atlas);
	e->atlas = NULL;
	m->tex_width = FRAMEW;
	m->tex_height = FRAMEH;
}
