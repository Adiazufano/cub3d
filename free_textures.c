/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:55:19 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/15 15:47:47 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture_bytes(t_tex_bytes *t)
{
	if (!t)
		return ;
	free(t->pixels);
	free(t);
}

void	free_wall_textures(t_map *m)
{
	free_texture_bytes(m->textures->north_tetxure);
	free_texture_bytes(m->textures->south_texture);
	free_texture_bytes(m->textures->west_texture);
	free_texture_bytes(m->textures->east_texture);
}
