/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:02:02 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/21 12:45:45 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapwidth][mapheight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
    m->key = malloc(sizeof(t_keys));
    if(!m->key)
        return(0);
    memset(m->key, 0, sizeof(t_keys));    
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

/*  FUNCION QUE PINTA TODA LA PNATALLA DE NEGRO PARA REFRESCAR Y QUE NO
*   SE SUPERPONGAN LOS PIXELES DEL TRAZADO DE RAYOS*/

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


/*  PINTAMOS EL CIELO Y EL SUELO ANTES DE PINTAR LOS MUROS POR ENCIMA
*   ESTA FUNCIÓN PINTA CADA MITAD DE LA PANTALLA DE UN COLOR */

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
                mlx_put_pixel(m->image, x, y, 0x000000FF);
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
    paint_image(m);                         // Pintamos cada mitad de la pantalla de un color.
    movement(m);                            // Calculamos los movimientos del jugador y recalculamos las variables.
    raycasting(m->player, m);               // Pintamos realizando el trazado de rayos para pintar los muros.
}

void setup_window(t_map *m)
{
    mlx_image_to_window(m->mlx, m->image, 0, 0);
    mlx_key_hook(m->mlx, key_event, m);
    mlx_loop_hook(m->mlx, game_loop, m);  
}