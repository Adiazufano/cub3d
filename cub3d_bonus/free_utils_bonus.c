/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:23:14 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/15 15:37:04 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_pixeles(t_map *m)
{
	int	i;

	i = 0;
	if (m->texture_info)
	{
		free (m->texture_info->heights);
		free (m->texture_info->widths);
		while (i < m->texture_info->count)
		{
			free (m->texture_info->pixeles[i]);
			i++;
		}
		free (m->texture_info->pixeles);
	}
}

void	free_slice_texture(mlx_texture_t *tex)
{
	if (!tex)
		return ;
	free (tex->pixels);
	free (tex);
}

void	free_textures(t_anim_ene *e)
{
	int	i;

	i = 0;
	while (i < e->walk_count)
	{
		free_slice_texture (e->walk[i]);
		i++;
	}
}

void	free_utils_close(t_cubed *cub3d, t_map *m, t_player *p)
{
	free (p->buffer_col);
	free (p);
	free_textures(m->e_text);
	free (m->helper);
	free (m->enemy);
	free_pixeles (m);
	free (m->texture_info);
	free (m->texture_enemy);
	free (m->e_text);
	free (m->portal);
	free (m->key);
	free_list (cub3d->enemy);
	free_cub3d (cub3d);
	free_wall_textures(m);
	free(m->texture);
}
