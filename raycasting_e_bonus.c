/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_e_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:20 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/05 17:29:37 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_sprite(t_player *p, t_enemy *e, t_map *m)
{
    uint32_t    color;
    t_tex_info *ti;
    double      margin;
    int         stripe;
    int         tex_width;
    int         tex_height;
    int         y;
    int         d;
    int         sprite_l;
    int         tex_x;
    int         tex_y;
    int         alpha;

    if (!e || !m || !m->texture_info)
        return;
    ti = m->texture_info;

    if (e->tex_id < 0 || e->tex_id >= ti->count)
        return;

    margin  = e->transform_y * -0.5;
    stripe = e->draw_start_x;

    /* dimensiones reales de esta textura */
    tex_width  = ti->widths[e->tex_id];
    tex_height = ti->heights[e->tex_id];

    while (stripe < e->draw_end_x)
    {
        sprite_l = e->screen_x - e->sprite_width / 2;

        /* tex_x usando ancho real */
        tex_x = (stripe - sprite_l) * tex_width / e->sprite_width;
        if (tex_x < 0)
            tex_x = 0;
        if (tex_x >= tex_width)
            tex_x = tex_width - 1;

        if (e->transform_y > 0 && stripe >= 0 && stripe < m->width &&
            e->transform_y < p->buffer_col[stripe] - margin)
        {
            y = e->draw_start_y;
            while (y < e->draw_end_y)
            {
                /* tex_y proporcional usando altura real */
                /* aquí mapeamos la franja vertical del sprite [draw_start_y..draw_end_y)
                   sobre [0..tex_height) */
                d = (y - e->draw_start_y) * tex_height;
                tex_y = d / e->sprite_height;
                if (tex_y < 0)
                    tex_y = 0;
                if (tex_y >= tex_height)
                    tex_y = tex_height - 1;

                color = ti->pixeles[e->tex_id][tex_y * tex_width + tex_x];
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
    if(e->sprite_height <= 0)
        e->sprite_height = 1;
    e->sprite_width = abs((int)(m->height / tz));
    if(e->sprite_width <= 0)
        e->sprite_width = 1;
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

void    enemy_position(t_player *p, t_enemy *e)
{
    double inv_det;
    
    e->dx = e->pos_x - p->pos_col;                                                  // Posición con respecto al jugador.
    e->dy = (e->pos_y + 0.5) - p->pos_row;
    inv_det = 1.0 / (p->plane_x * p->direct_y - p->direct_x * p->plane_y);
    e->transform_x = inv_det * (p->direct_y * e->dx - p->direct_x * e->dy);         // Posición en cámara con respecto al jugador del enemigo. (es el equivalente a perp_wall_dist)
    e->transform_y = inv_det * (-p->plane_y * e->dx + p->plane_x * e->dy);          // Si esta linea es mayor de 0 el enemigo está a la espalda.
    e->enemy_distance = e->dx * e->dx + e->dy * e->dy;               
}

int map_is_wall(t_map *m, int mx, int my)
{
    if (!m || !m->map)
        return (1);
    if (my < 0 || mx < 0)
        return (1);
    if (!m->map[my])
        return (1);
    if (m->map[my][mx] == '\0')
        return (1);
    return (m->map[my][mx] == '1');
}

int enemy_can_see_palyer(t_player *p, t_enemy *e, t_map *m, double max_dist)
{
    double  vx;
    double  vy;
    double  dist;
    double  step;
    double  t;
    double  nx;
    double  ny;

    if (!p || !e || !m)
        return (0);
    vx = p->pos_col - e->pos_x;
    vy = p->pos_row - e->pos_y;
    dist = sqrt(vx * vx + vy * vy);
    step = 0.1;
    if (dist > max_dist)
        return (0);
    if (dist < 1e-6)
        return (1);
    vx /= dist;
    vy /= dist;
    t = 0.0;
    while (t < dist)
    {
        nx = e->pos_x + vx * t;
        ny = e->pos_y + vy * t;
        if (map_is_wall(m, (int)nx, (int)ny))
            return (0);
        t += step;
    }
    return (1);
}

void    move_enemy_towards_player(t_player *p, t_enemy *e, t_map *m, double dt)
{
    double  vx;
    double  vy;
    double  len;
    double  move_x;
    double  move_y;
    double  step_size;
    int     steps;
    double  step_x;
    double  step_y;
    int     i;

    if (!p || !e || !m || dt <= 0.0)
        return ;
    vx = p->pos_col - e->pos_x;
    vy = p->pos_row - e->pos_y;
    len = sqrt(vx * vx + vy * vy);
    if (len < 1e-6)
        return ;
    vx /= len;
    vy /= len;

    /* velocidad del enemigo (unidades por segundo). Ajustar según sea necesario */
    const double speed = 2.5;

    /* desplazamiento total previsto para este frame */
    move_x = vx * speed * dt;
    move_y = vy * speed * dt;

    /* tamaño de paso para la comprobación de colisión (menor => más preciso) */
    step_size = 0.1;
    steps = (int)ceil(fmax(fabs(move_x), fabs(move_y)) / step_size);
    if (steps < 1)
        steps = 1;
    step_x = move_x / (double)steps;
    step_y = move_y / (double)steps;

    for (i = 0; i < steps; ++i)
    {
        double try_x = e->pos_x + step_x;
        double try_y = e->pos_y + step_y;

        /* comprobar eje X por separado (permite deslizarse a lo largo de paredes) */
        if (!map_is_wall(m, (int)try_x, (int)e->pos_y))
            e->pos_x = try_x;
        else
            step_x = 0.0; /* inhibir movimiento X futuros de este frame */

        /* comprobar eje Y por separado */
        if (!map_is_wall(m, (int)e->pos_x, (int)try_y))
            e->pos_y = try_y;
        else
            step_y = 0.0; /* inhibir movimiento Y futuros de este frame */

        if (step_x == 0.0 && step_y == 0.0)
            break;
    }
}

void    update_enemies(t_player *p, t_enemy **enemy_head, t_map *m, double dt)
{
    t_enemy *it;
    double max_see_dist;

    if (!p || !enemy_head || !m)
        return;
    it = *enemy_head;
    max_see_dist = 12.0;

    /* DEBUG: contar y listar enemigos antes de mover */
    int count = 0;
    t_enemy *tmp = it;
    while (tmp)
    {
        printf("DEBUG: enemy %p pos=(%.2f,%.2f) dist_sq=%.2f\n",
               (void*)tmp, tmp->pos_x, tmp->pos_y, tmp->enemy_distance);
        count++;
        tmp = tmp->next;
    }
    printf("DEBUG: total enemies = %d\n", count);

    while (it)
    {
        int can_see = enemy_can_see_palyer(p, it, m, max_see_dist);
        printf("DEBUG: enemy %p can_see=%d\n", (void*)it, can_see);
        if (can_see)
            move_enemy_towards_player(p, it, m, dt);
        it = it->next;
    }
}


int     raycasting_enemy(t_player *p, t_enemy **enemy, t_map *m)
{
    t_enemy *tmp;

    tmp = *enemy;
    (void) m;
    while(tmp)
    {
        enemy_position(p, tmp);
        tmp = tmp->next;
    }
    update_enemies(p, enemy, m, 0.016);

    /* RECOMPUTAR transform después de moverlos */
    tmp = *enemy;
    while (tmp)
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

