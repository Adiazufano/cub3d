/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:14 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/17 13:35:47 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	scale_sword(t_map *m, mlx_image_t *img)
{
	float	scale_factor;
	int		img_w;
	int		img_h;

	scale_factor = (float)m->height / 480;
	img_w = 64 * 4 * scale_factor;
	img_h = 64 * 4 * scale_factor;
	if (mlx_resize_image(img, img_w, img_h) == false)
	{
		printf("Error\n");
		exit(1);
	}
	mlx_image_to_window(m -> mlx, img, ((m->width - img_w) / 2),
		(m->height - img_h));
}

void	paint_sword(t_map *m)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png("./textures/Portal_Gun.png");
	if (!tex)
		exit(1);
	img = mlx_texture_to_image(m -> mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
	{
		printf("Error\n");
		exit(1);
	}
	scale_sword(m, img);
}
