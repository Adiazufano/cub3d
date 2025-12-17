/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:55:19 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/15 15:48:44 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_textures_map(t_map *m)
{
	m->texture->north_tetxure
		= load_texture_bytes(m -> cub3d -> north_texture);
	m->texture->east_texture
		= load_texture_bytes(m -> cub3d -> east_texture);
	m->texture->west_texture
		= load_texture_bytes(m -> cub3d -> west_texture);
	m->texture->south_texture
		= load_texture_bytes(m -> cub3d -> south_texture);
	m->texture->door_texture
		= load_texture_bytes(m -> cub3d -> door_texture);
	m->texture->open_portal_texture
		= load_texture_bytes(m -> cub3d -> open_portal_texture);
	m->texture->close_portal_texture
		= load_texture_bytes(m -> cub3d -> close_portal_texture);
}

void	free_texture_bytes(t_tex_bytes *t)
{
	if (!t)
		return ;
	free(t->pixels);
	free(t);
}

void	free_wall_textures(t_map *m)
{
	free_texture_bytes(m->texture->north_tetxure);
	free_texture_bytes(m->texture->south_texture);
	free_texture_bytes(m->texture->west_texture);
	free_texture_bytes(m->texture->east_texture);
	free_texture_bytes(m->texture->door_texture);
	free_texture_bytes(m->texture->open_portal_texture);
	free_texture_bytes(m->texture->close_portal_texture);
}
