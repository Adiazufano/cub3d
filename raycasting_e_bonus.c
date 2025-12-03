/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_e_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:20 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/03 17:40:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    draw_sprite(t_player *p, t_enemy *e, t_map *m)
{
    int stripe;
    int y;
    int d;
    int sprite_l;
    int tex_x;
    int tex_y;
    int color;
    int alpha;
    
    if (!e || !m || !m->sprite_textures)
        return ;
    if (e->tex_id < 0 || e->tex_id >= m->n_sprites)
        return ;
    stripe = e->draw_start_x;
    while (stripe < e->draw_end_x)
    {
        sprite_l = e->screen_x - e->sprite_width / 2;
        tex_x = (int)(256 * (stripe - sprite_l) * m->tex_width / e->sprite_width) / 256;
        if (tex_x < 0)
            tex_x = 0; 
        if (tex_x >= m->tex_width)
            tex_x = m->tex_width - 1;
        if (e->transform_y > 0 && stripe >= 0 && stripe < m->width && e->transform_y < p->buffer_col[stripe])
        {
            y = e->draw_start_y;
            while (y < e->draw_end_y)
            {
                d = (y) * 256 - m->height * 128 + e->sprite_height * 128;
                tex_y = (d * m->tex_height /e->sprite_height) / 256;
                if (tex_y < 0)
                    tex_y = 0;
                if (tex_y >= m->tex_height)
                    tex_y = m->tex_height - 1;
                color = m->sprite_textures[e->tex_id][tex_y * m->tex_width + tex_x];
                alpha = (color >> 24) & 0xFF;
                if (alpha != 0)
                    mlx_put_pixel(m->image, (uint32_t)stripe, (uint32_t)y, color);
                y++;
            }
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
    double  tz;
    
    tz = e->transform_y;
    if (tz == 0.0)                                                                      // Condición de seguridad
        tz = 1e-6;
    e->screen_x = (int)((m->width / 2) * (1 + e->transform_x / tz));       // Columna donde se va a dibujar el sprite
    e->sprite_height = abs((int)(m->height / tz));
    e->sprite_width = abs((int)(m->height / tz));
    e->draw_start_x = e->screen_x - e->sprite_width/2;
    if (e->draw_start_x < 0)
        e->draw_start_x = 0;
    e->draw_end_x = e->screen_x + e->sprite_width/2;
    if (e->draw_end_x >= m->width)
        e->draw_end_x = m->width -1;        
    e->draw_start_y = -e->sprite_height / 2 + m->height / 2;
    if (e->draw_start_y < 0)
        e->draw_start_y = 0;
    e->draw_end_y = e->sprite_height / 2 + m->height / 2;
    if (e->draw_end_y >= m->height)
        e->draw_end_y = m->height - 1;      
}  

void    sort_enemies(t_enemy **enemy)
{
    t_enemy **ptr;
    t_enemy *lptr;
    t_enemy *tmp;
    int     swapped;
    
    if(!enemy || !*enemy)
        return ;
    lptr = NULL;
    swapped = 1;
    while(swapped)
    {
        swapped = 0;
        ptr = enemy;                                            // Puntero doble que apunta a next del nodo anterior.
        while((*ptr)->next != lptr)
        {
            if((*ptr)->enemy_distance < (*ptr)->next->enemy_distance)
            {
                /* Intercambio de nodos */
                tmp = (*ptr)->next;
                (*ptr)->next = tmp->next;
                tmp->next = *ptr;                                // Actualizamos el puntero anterior para que apunte al nuevo primer nodo.
                *ptr = tmp;
                swapped = 1;                                         
            }
            else
                ptr = &(*ptr)->next;                            // Solo avanzamos si no hubo intercambio para evitar que no se comparen correctamente todos los pares.
        }
        lptr = *ptr;                                            // Fijamos el último nodo de la lista.
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


void  enemy_position(t_player *p, t_enemy *e)
{
    double inv_det;
    
    e->dx = e->pos_x - p->pos_col;                                                  // Posición con respecto al jugador.
    e->dy = e->pos_y - p->pos_row;
    inv_det = 1.0 / (p->plane_x * p->direct_y - p->direct_x * p->plane_y);
    e->transform_x = inv_det * (p->direct_y * e->dx - p->direct_x * e->dy);         // Posición en cámara con respecto al jugador del enemigo. (es el equivalente a perp_wall_dist)
    e->transform_y = inv_det * (-p->plane_y * e->dx + p->plane_x * e->dy);          // Si esta linea es mayor de 0 el enemigo está a la espalda.
    e->enemy_distance = e->dx * e->dx + e->dy * e->dy;         
}


int     raycasting_enemy(t_player *p, t_enemy **enemy, t_map *m)
{
    t_enemy *tmp;

    tmp = *enemy;
    while(tmp)
    {
        enemy_position(p, tmp);
        tmp = tmp->next;
    }
    sort_enemies(enemy);
    tmp = *enemy;
    while(tmp)
    {
        if (tmp->transform_y > 0)
        {
            size_correlation(tmp, m);
            draw_sprite(p, tmp, m);
        }
        tmp = tmp->next;
    }
	return (1);
}

