/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:27:01 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/24 14:21:22 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* El vector de dirección define hacia donde miras. Vamos a tener en consideración la orientación inicial que nos pasen en el parseo 
* El plano de cámara ha de ser perpendicular al vector de dirección
* La fórmula para inicializar el plano es la siguiente:

plane_x = dir_y * fov_factor;
plane_y = -dir_x * fov_factor;
*/

void init_pos_and_orinetation(t_map *m, t_player *p)
{
    int j;
    int i;
    char c;
    
    i = 0;
    while (m -> map[i])
    {
        j = 0;
        while (m -> map[i][j])
        {
            c = m -> map[i][j];
            if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
            {
                p->pos_row = (double)i + 0.5;
                p->pos_col = (double)j + 0.5;
                m -> orientation = c;
            }
            j++;
        }
        i++;
    }
}

void initialize(t_player *p, t_map *m,  t_cubed *cub3d)
{
    m->height = HEIGHT;
    m->width = WIDTH;
    m -> map = cub3d -> map;
    init_pos_and_orinetation(m, p);
    p->fov = 0.66;
    p->time = 0;
    p->oldtime = 0;
    initialize_direction(p, m);
    p->mov_Speed = 0.05;
    p->rot_Speed = 0.03;
    p->pitch = 0;
    p->speed_ratio = 1;
    p->plane_x = -p->direct_y * p->fov;
    p->plane_y = p->direct_x * p->fov;
}

/* Dirección del jugador. No puede ser 0.0 ya que eso haría que el cálculo de trazado de rayos fuese erroneo */

void initialize_direction(t_player *p, t_map *m)
{
    if(m->orientation == 'N')
    {  
        p->direct_x = -1.0;  // Norte = X negativo
        p->direct_y = 0.0;
    }
    if(m->orientation == 'S') 
    {  
        p->direct_x = 1.0;   // Sur = X positivo
        p->direct_y = 0.0;
    }
    if(m->orientation == 'W')
    {  
        p->direct_x = 0.0;
        p->direct_y = -1.0;  // Oeste = Y negativo
    }
    if(m->orientation == 'E')
    {  
        p->direct_x = 0.0;
        p->direct_y = 1.0;   // Este = Y positivo
    }
}
