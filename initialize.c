/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:27:01 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/19 10:00:44 by mparra-s         ###   ########.fr       */
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


void initialize(t_player *p, t_map *m)
{
    m->orientation = 'N';
    m->height = HEIGHT;
    m->width = WIDTH;
    p->pos_row = 2.0;                 //Posición en el mapa. Cuando tenga el mapa introducir una posición correcta.
    p->pos_col = 3.0;
    p->fov = 0.66;
    p->time = 0;                    //Tiempo del frame actual.
    p->oldtime = 0;                 //Tiempo del frame antiguo.
    initialize_direction(p, m);
    p->plane_x = -p->direct_y * p->fov;             //Tiene que ser negativo para representar que sea perpendicular al eje de visión.
    p->plane_y = p->direct_x * p->fov;
}

/* Dirección del jugador. No puede ser 0.0 ya que eso haría que el cálculo de trazado de rayos fuese erroneo */

void initialize_direction(t_player *p, t_map *m)
{
    if(m->orientation == 'N')
    {  
        p->direct_x = 0.0;
        p->direct_y = 1.0;
    }
    if(m->orientation == 'S') 
    {  
        p->direct_x = 0.0;
        p->direct_y = -1.0;
    }
    if(m->orientation == 'W')
    {  
        p->direct_x = -1.0;
        p->direct_y = 0.0;
    }
    if(m->orientation == 'E')
    {  
        p->direct_x = 1.0;
        p->direct_y = 0.0;
    }
}
