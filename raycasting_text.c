/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:32:04 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 10:34:16 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex_bytes	*select_texture(t_textures *tetxures, t_map *m, t_player *p)
{
	t_tex_bytes	*current;

	current = NULL;
	if (p->side == 0)
	{
		if (p->step_x > 0)
			current = tetxures->north_tetxure;
		else
			current = tetxures->south_texture;
	}
	else
	{
		if (p->step_y > 0)
			current = tetxures->west_texture;
		else
			current = tetxures->east_texture;
	}
	if (p->map_x >= 0 && p->map_x < m->height)
	{
		if (p->map_y >= 0 && p->map_y < (int)ft_strlen(m->map[p->map_x]))
			if (m->map[p->map_x][p->map_y] == '3'
				&& tetxures->door_texture)
				current = tetxures->door_texture;
	}
	return (current);
}

int	raycasting(t_player *p, t_map *m)
{
	static t_textures	textures;
	static int			textures_load;

	if (!textures_load)
	{
		textures.north_tetxure
			= load_texture_bytes(m -> cub3d -> north_texture);
		textures.east_texture
			= load_texture_bytes(m -> cub3d -> east_texture);
		textures.west_texture
			= load_texture_bytes(m -> cub3d -> west_texture);
		textures.south_texture
			= load_texture_bytes(m -> cub3d -> south_texture);
		textures.door_texture
			= load_texture_bytes(m->cub3d->door_texture);
		textures_load = 1;
	}
	if (!m->image || !m->image->pixels)
		return (0);
	raycasting_draw_utils(p, m, &textures);
	return (1);
}

void	init_draw_col(t_tex_bytes *t, t_draw_col *dc, t_map *m, t_player *p)
{
	dc->screen = m->image->pixels;
	dc->screen_w = m->width;
	dc->screen_h = m->height;
	dc->draw_start = p->init_draw;
	dc->draw_end = p->finish_draw;
	dc->line_height = p->line_height;
	dc->side = p->side;
	dc->ray_dir_x = p->dirray_x;
	dc->ray_dir_y = p->dirray_y;
	dc->pitch = p->pitch;
	dc->tex = t;
}
