/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/18 11:30:05 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3D.h"

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


int main(int argc, char **argv)
{
    t_map   m = {0};
    
    (void)argv;
    (void)argc;
    if(!init_cube(&m))
        return(1);
    setup_window(&m);
    mlx_loop(m.mlx);
    mlx_terminate(m.mlx);
    free(m.player);   
    return (0);
}