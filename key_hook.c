/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:02:12 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/25 09:18:58 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/* FUNCIÓN PARA CONTROLAR LAS PRESIÓN DE LAS TECLAS */

void key_event(mlx_key_data_t key_code, void *param)
{
    t_map *m;
    int pressed;
    int released;
    
    m = param;
    pressed = (key_code.action == MLX_PRESS || key_code.action == MLX_REPEAT);
    released = (key_code.action == MLX_RELEASE);
    if(key_code.key == MLX_KEY_W)
        m->key->W = pressed && !released;
    if(key_code.key == MLX_KEY_S)
        m->key->S = pressed && !released;
    if(key_code.key == MLX_KEY_A)
        m->key->A = pressed && !released;
    if(key_code.key == MLX_KEY_D)
        m->key->D = pressed && !released;
    if(key_code.key == MLX_KEY_E && key_code.action == MLX_PRESS)
        door(m);
    if(key_code.key == MLX_KEY_C && key_code.action == MLX_PRESS)
        move_pov(m);
    if(key_code.key == MLX_KEY_LEFT_SHIFT)
        m->player->sprint = pressed && !released;    
    if(key_code.key == MLX_KEY_LEFT)
        m->key->LEFT = pressed && !released;
    if(key_code.key == MLX_KEY_RIGHT)
        m->key->RIGHT = pressed && !released;
    if(key_code.key == MLX_KEY_ESCAPE)
        mlx_close_window(m->mlx);
}

void door(t_map *m)
{
    t_player *p;
    int front_row;
    int front_col;

    p = m->player;
    front_row = p->pos_row + p->direct_x * 0.9;
    front_col = p->pos_col + p->direct_y * 0.9;
    if(m->map[front_row][front_col] == 3)
        m->map[front_row][front_col] = 2;
    else if (m->map[front_row][front_col] == 2)
        m->map[front_row][front_col] = 3;
}
/*  FUNCIÓN QUE INICIALIZA EL RATÓN PARA REALIZAR EL GIRO DE CÁMARA. */

void rotation_mouse(t_map *m)
{
    t_player *p;
    int32_t old_dir_x;                                      // Inicializamos las variables para las coordenadas en X e Y del ratón.
    int32_t old_dir_y;
    double diff;
    double sensitivity;                                     // Añadimos la sensibilidad con la que se ha de mover el ratón.

    p = m->player;
    sensitivity = 0.002;                                    // Ratio movimiento del ratón.                                       
    mlx_get_mouse_pos(m->mlx, &old_dir_x, &old_dir_y);      // Esta función establece la posición en la que se encuentra el cursor.
    diff = old_dir_x - (WIDTH / 2);                         
    rotate_player(m, - diff * sensitivity);                 // Función que rota el jugador.
    mlx_set_cursor_mode(m->mlx, MLX_MOUSE_DISABLED);        // Función que invisibiliza el cursor.
    mlx_set_mouse_pos(m->mlx, WIDTH / 2, HEIGHT / 2);       // Función que sitúa el cursor en el centro de la pantalla. 
}

/* FUNCIÓN QUE ROTA EL CAMPO DE VISIÓN DEL PERSONAJE CON EL RATÓN */

void rotate_player(t_map *m, double rot)
{
    t_player *p;
    double old_dir;
    double old_plane;

    p = m->player;
    old_dir = p->direct_x;
    p->direct_x = p->direct_x * cos(rot) - p->direct_y * sin(rot);          // Cambia el vector director del personaje.
    p->direct_y = old_dir * sin(rot) + p->direct_y * cos(rot);
    old_plane = p->plane_x;
    p->plane_x = p->plane_x * cos(rot) - p->direct_y * sin(rot);            // Cambia el plano de representación del personaje.
    p->plane_y = old_plane * sin(rot) + p->direct_y * cos(rot);
}