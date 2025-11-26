/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:54:26 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/26 15:59:46 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    door(t_map *m)
{
    t_player    *p;
    int         front_row;
    int         front_col;

    p = m->player;
    front_row = p->pos_row + p->direct_x * 0.9;
    front_col = p->pos_col + p->direct_y * 0.9;
    if (m->map[front_row][front_col] == '3')
        m->map[front_row][front_col] = '2';
    else if (m->map[front_row][front_col] == '2')
        m->map[front_row][front_col] = '3';
}

/* FUNCIÓN PARA CONTROLAR LAS PRESIÓN DE LAS TECLAS */

void key_event(mlx_key_data_t key_code, void *param)
{
    t_map *m;
    int pressed;
    int released;
    
    m = param;
    pressed = (key_code.action == MLX_PRESS || key_code.action == MLX_REPEAT);
    released = (key_code.action == MLX_RELEASE);
    key_move_event(key_code, m);
    if (key_code.key == MLX_KEY_E && key_code.action == MLX_PRESS)
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

void key_move_event(mlx_key_data_t key_code, void *param)
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
}

/* FUNCIÓN PARA DETERMINAR EL MOVIMIENTO DEL PERSONAJE. ESTABLECEMOS CONTROL DE MURO PARA NO CHOCAR*/

void rotation_mouse(t_map *m)
{
    t_player *p;
    int32_t mouse_x;
    int32_t mouse_y;
    double diff;
    double sensitivity;
    static int first_frame = 1;  // Flag para ignorar el primer frame
    p = m->player;
    sensitivity = 0.002; 
    mlx_get_mouse_pos(m->mlx, &mouse_x, &mouse_y);    
    // En el primer frame, solo centrar el mouse sin rotar
    if (first_frame)
    {
        first_frame = 0;
        mlx_set_cursor_mode(m->mlx, MLX_MOUSE_DISABLED);
        mlx_set_mouse_pos(m->mlx, WIDTH / 2, HEIGHT / 2);
        return;
    }    
    diff = mouse_x - (WIDTH / 2);    
    // Solo rotar si el movimiento del mouse es significativo
    if (fabs(diff) > 1.0)  // Tolerancia de 1 píxel
        rotate_player(m,  diff * sensitivity);    
    mlx_set_cursor_mode(m->mlx, MLX_MOUSE_DISABLED);
    mlx_set_mouse_pos(m->mlx, WIDTH / 2, HEIGHT / 2);
}

void rotate_player(t_map *m, double rot)
{
    t_player *p;
    double old_dir;
    double old_plane;

    p = m->player;
    old_dir = p->direct_x;
    p->direct_x = p->direct_x * cos(rot) - p->direct_y * sin(rot);
    p->direct_y = old_dir * sin(rot) + p->direct_y * cos(rot);
    old_plane = p->plane_x;
    p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
    p->plane_y = old_plane * sin(rot) + p->plane_y * cos(rot);
}