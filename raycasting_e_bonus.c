/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_e_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:20 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/02 17:35:50 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    draw_sprite(t_player *p, t_enemy *e, t_map *m)
{
    int stripe;
    
    stripe = e->draw_start_x;
    while(stripe < e->draw_end_x)
    {
        if(e->transform_y > 0 && stripe >= 0 && stripe < m->width && e->transform_y < p->buffer_col[stripe])
        {
            /*print sprite*/
        }
        stripe++;
    }    
} 


/********************************************************************************/
/*  Esta función determina la columna donde pintar el sprite y además se        */
/*  encarga de calcular la relación de tamaño en función de la distancia        */
/********************************************************************************/

void    size_correlation(t_enemy *e, t_map *m)
{    
    e->screen_x = (int)((m->width / 2) * (1 + e->transform_x / e->transform_y));       // Columna donde se va a dibujar el sprite
    e->sprite_height = abs((int)(m->height / e->transform_y));
    e->sprite_width = abs((int)(m->height / e->transform_y));
    e->draw_start_x = e->screen_x - e->sprite_width/2;
    if(e->draw_start_x < 0)
        e->draw_start_x = 0;
    e->draw_end_x = e->screen_x + e->sprite_width/2;
    if(e->draw_end_x >= m->width)
        e->draw_end_x = m->width -1;        
    e->draw_start_y = -e->sprite_height / 2 + m->height / 2;
    if(e->draw_start_y < 0)
        e->draw_start_y = 0;
    e->draw_end_y = e->sprite_height / 2 + m->height / 2;
    if(e->draw_end_y >= m->height)
        e->draw_end_y = m->height - 1;      
}  

void    sort_enemies(t_enemy *enemy, t_player *p)
{
    t_enemy *ptr;
    t_enemy *lptr;
    int     swapped;
    double  tx;
    double  ty;
    double  tdx;
    double  tdy;
    double  txformx;
    double  tyformy;
    int     tlife;

    tx = enemy->pos_x;
    ty = enemy->pos_y;
    tlife = enemy->life; 
    tdx = enemy->dx;
    tdy = enemy->dy;
    txformx = enemy->transform_x;
    tyformy = enemy->transform_y;
    swapped = 1;
    lptr = NULL;
    if(!enemy)
        return ;
    while(swapped)
    {
        swapped = 0;
        ptr = enemy;
        while(ptr->next != lptr)
        {
            if(enemy_position(p, ptr) < enemy_position(p, ptr->next))
            {
                ptr->pos_x = ptr->next->pos_x;
                ptr->next->pos_x = tx;
                ptr->pos_y = ptr->next->pos_y;
                ptr->next->pos_y = ty;
                ptr->life = ptr->next->life;
                ptr->next->life = tlife;
                ptr->dx = ptr->next->dx;
                ptr->next->dx = tdx;
                ptr->dy = ptr->next->dy;
                ptr->next->dy = tdy;
                ptr->transform_x = ptr->next->transform_x;
                ptr->next->transform_x = txformx;
                ptr->transform_y = ptr->next->transform_y;
                ptr->next->transform_y = tyformy;
                swapped = 1;                        
            }
            ptr = ptr->next;
        }
        lptr = ptr;        
    }            
}


/********************************************************************************/
/*  Esta función obtiene la distancia del enemigo al jugador con dx y dy y los  */
/*  utiliza para calcular la posición relativa al espacio de al cámara          */
/*                                                                              */
/*  Trasform_y > 0 significa que el enemigo está a la espalda del jugador       */
/*  Transform_x / Transform_y es la poisición horizontal en pantalla            */
/*  1 / Transform_y escala del sprite (altura y ancho)                          */
/********************************************************************************/

double    enemy_position(t_player *p, t_enemy *e)
{
    double inv_det;
    
    e->dx = e->pos_x - p->pos_col;                                                  // Posición con respecto al jugador.
    e->dy = e->pos_y - p->pos_row;
    inv_det = 1.0 / (p->plane_x * p->direct_y - p->direct_x * p->plane_y);
    e->transform_x = inv_det * (p->direct_y * e->dx - p->direct_x * e->dy);         // Posición en cámara con respecto al jugador del enemigo. (es el equivalente a perp_wall_dist)
    e->transform_y = inv_det * (-p->plane_y * e->dx + p->plane_x * e->dy);          // Si esta linea es mayor de 0 el enemigo está a la espalda.
    return(e->dx * e->dx + e->dy * e->dy);            
}


int     raycasting_enemy(t_player *p, t_enemy *e_array, t_map *m)
{
    while(e_array)
    {
        enemy_position(p, e_array);
        size_correlation(e_array, m);
        draw_sprite(p, e_array, m);
        e_array = e_array->next;
    }
	return (1);
}

