/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:14:46 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:21:46 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	alloc_resources(t_map *m)
{
	m->player = malloc (sizeof (t_player));
	if (!m->player)
		return (0);
	m->portal = malloc (sizeof(t_portal));
	if (!m->portal)
		return (0);
	m->enemy = malloc (sizeof(t_enemy));
	if (!m->enemy)
		return (0);
	m->helper = malloc (sizeof(*m->helper));
	if (!m->helper)
		return (0);
	m->key = malloc(sizeof(*(m->key)));
	if (!m->key)
		return (0);
	m->e_text = malloc(sizeof(t_anim_ene));
	if (!m->e_text)
		return (0);
	return (1);
}

int	init_cube(t_map *m, t_cubed *cub3d)
{
	if (!alloc_resources(m))
		return (0);
	m->mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!m->mlx)
	{
		write (2, "Error: Imposible to create MLX\n", 32);
		return (0);
	}
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	if (!m->mlx || !m->image)
	{
		write (2, "Error: Imposible to create the image\n", 38);
		return (0);
	}
	initialize_bonus(m->player, m, cub3d, m->portal);
	load_ene_text(m->e_text, m);
	return (1);
}
