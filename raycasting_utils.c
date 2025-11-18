/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/18 12:49:20 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapwidth][mapheight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void initialize_map(t_map *m)
{
    for (int i = 0; i < mapwidth; i++)
        for (int j = 0; j < mapheight; j++)
            m->map[i][j] = worldMap[i][j];
}

int init_cube(t_map *m)
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
    initialize(m->player, m);
    initialize_map(m);
    return(1);   
}

void setup_window(t_map *m)
{
    (void)m;    
}