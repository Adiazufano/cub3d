/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:14 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/11 18:44:29 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	paint_sword(t_map *m)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	int				img_w;
	int				img_h;

	img_w = 64 * 3;
	img_h = 64 * 3;
	tex = mlx_load_png("./textures/Portal_Gun.png");
	if (!tex)
		return ;
	img = mlx_texture_to_image(m -> mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
	{
		printf("Error\n");
		exit(1);
	}
	if (mlx_resize_image(img, 64 * 5, 64 * 5) == false)
	{
		printf("Error\n");
		exit(1);
	}
	mlx_image_to_window(m -> mlx, img, ((m->width - img_w) / 2),
		((m->height - img_h) / 1.5));
}
