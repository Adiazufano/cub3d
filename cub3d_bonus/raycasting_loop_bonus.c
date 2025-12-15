/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:16:55 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:21:28 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	game_loop(void *param)
{
	t_map	*m;

	m = (t_map *)param;
	clear_image(m);
	paint_image(m);
	movement(m);
	raycasting(m->player, m);
	raycasting_enemy(m->player, &m->cub3d->enemy, m);
	paint_minimap(m);
	paint_sword(m);
}

void	setup_window(t_map *m)
{
	mlx_image_to_window(m->mlx, m->image, 0, 0);
	mlx_key_hook(m->mlx, key_event, m);
	mlx_loop_hook(m->mlx, game_loop, m);
}
