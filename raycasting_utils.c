/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/21 19:12:31 by aldiaz-u         ###   ########.fr       */
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
    /* allocate and initialize key state to avoid NULL deref and sticky keys */
    m->key = malloc(sizeof(*(m->key)));
    if (!m->key)
        return (0);
    /* set all keys to 0 */
    m->key->W = 0;
    m->key->S = 0;
    m->key->A = 0;
    m->key->D = 0;
    m->key->LEFT = 0;
    m->key->RIGHT = 0;

    initialize(m->player, m, cub3d);
    return(1);   
}

void clear_image(t_map *m)
{
    int x;
    int y;
    
    y = 0;
    while(y < m->height)
    {
        x = 0;
        while(x < m->width)
        {
            mlx_put_pixel(m->image, x, y, 0x000000FF);
            x++;
        }
        y++;
    }    
}

void paint_image(t_map *m)
{
    int x;
    int y;

    y = 0;
    while(y < m->height)
    {
        x = 0;
        while(x < m->width)
        {
            if(y < (m->height / 2))
                mlx_put_pixel(m->image, x, y, 0x00FF0000);
            else
                mlx_put_pixel(m->image, x, y, 0x000000FF);
            x++;
        }
        y++;
    }
}

void game_loop(void *param)
{
    t_map *m = (t_map *)param;
    clear_image(m);
    paint_image(m);
    movement(m);
    raycasting(m->player, m);
}

void setup_window(t_map *m)
{
    mlx_image_to_window(m->mlx, m->image, 0, 0);
    /* register key handler so key_event is called and updates m->key */
    mlx_key_hook(m->mlx, key_event, m);
    mlx_loop_hook(m->mlx, game_loop, m);
}