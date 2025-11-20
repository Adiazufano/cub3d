/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/20 10:44:13 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void initialize_map(t_map *m)
{
    for (int i = 0; i < mapwidth; i++)
        for (int j = 0; j < mapheight; j++)
            m->map[i][j] = worldMap[i][j];
} */

int init_cube(t_map *m, t_cubed *cub3d)
{
    m->player = malloc(sizeof(t_player));
    if(!m->player)
        return(0);
    m->mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
    if(!m->mlx)
    {
        write(2, "Error: Imposible to create MLX\n", 32);
        return(0);
    }
    m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
    if(!m->mlx || !m->image)
    {
        write(2, "Error: Imposible to create the image\n", 38);
        return(0);
    } 
    initialize(m->player, m, cub3d);
    return(1);   
}

void game_loop(void *param)
{
    t_map *m = (t_map *)param;
    raycasting(m->player, m);
}

void setup_window(t_map *m)
{
    mlx_image_to_window(m->mlx, m->image, 0, 0);
    mlx_loop_hook(m->mlx, game_loop, m);  
}