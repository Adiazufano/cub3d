/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:54:26 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/24 14:38:26 by aldiaz-u         ###   ########.fr       */
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
    if(key_code.key == MLX_KEY_C && key_code.action == MLX_PRESS)
        move_pov(m);
    if(key_code.key == MLX_KEY_LEFT)
        m->key->LEFT = pressed && !released;
    if(key_code.key == MLX_KEY_RIGHT)
        m->key->RIGHT = pressed && !released;
    if(key_code.key == MLX_KEY_ESCAPE)
        mlx_close_window(m->mlx);
}

void move_pov(t_map *m)
{
    if(m->player->pitch == 0)
    {
        m->player->pitch = 150;
        m->player->fov = 0.8;
        m->player->speed_ratio = 0.001;
    } 
    else
    {
        m->player->pitch = 0;
        m->player->fov = 0.66;
        m->player->speed_ratio = 10;
    }    
}


/* FUNCIÓN PARA DETERMINAR EL MOVIMIENTO DEL PERSONAJE. ESTABLECEMOS CONTROL DE MURO PARA NO CHOCAR*/


void movement(t_map *m)
{
    t_player *p;
    double diff;
    double new_pos_row;
    double new_pos_col;
    double margin;
    
    p = m->player;
    margin = 0.2;  // Margen de seguridad para no atravesar muros
    p->oldtime = p->time;
    p->time = mlx_get_time();
    diff = p->time - p->oldtime;
    p->mov_Speed = diff * 3.0;
    if(p->mov_Speed > 0.1)
        p->mov_Speed = 0.1;
    new_pos_row = p->pos_row;
    new_pos_col = p->pos_col;
    
    if(m->key->W)
    {
        new_pos_row += p->direct_x * p->mov_Speed;
        new_pos_col += p->direct_y * p->mov_Speed;
    }
    if(m->key->S)
    {
        new_pos_row -= p->direct_x * p->mov_Speed;
        new_pos_col -= p->direct_y * p->mov_Speed;
    }
    if(m->key->D)
    {
        new_pos_row -= p->direct_y * p->mov_Speed;
        new_pos_col += p->direct_x * p->mov_Speed;
    }
    if(m->key->A)
    {
        new_pos_row += p->direct_y * p->mov_Speed;
        new_pos_col -= p->direct_x * p->mov_Speed;
    }
    
    rotation(m);
    rotation_mouse(m);
    
    // Comprobar colisión con margen en X (filas)
    if (m->map[(int)(new_pos_row + margin)][(int)p->pos_col] != '1' &&
        m->map[(int)(new_pos_row - margin)][(int)p->pos_col] != '1')
        p->pos_row = new_pos_row;
    
    // Comprobar colisión con margen en Y (columnas)
    if (m->map[(int)p->pos_row][(int)(new_pos_col + margin)] != '1' &&
        m->map[(int)p->pos_row][(int)(new_pos_col - margin)] != '1')
        p->pos_col = new_pos_col;
}

/*  FUNCIÓN QUE CALCULA EL GIRO DEL PERSONAJE */

void rotation(t_map *m)
{
    t_player *p;
    double old_dir_x;                       
    double old_plane_x;
    
    p = m->player;
    if(m->key->RIGHT)
    {
        old_dir_x = p->direct_x;
        p->direct_x = p->direct_x * cos(p->rot_Speed) - p->direct_y * sin(p->rot_Speed);  // Quitar el signo negativo
        p->direct_y = old_dir_x * sin(p->rot_Speed) + p->direct_y * cos(p->rot_Speed);
        old_plane_x = p->plane_x;
        p->plane_x = p->plane_x * cos(p->rot_Speed) -p->plane_y * sin(p->rot_Speed);
        p->plane_y = old_plane_x * sin(p->rot_Speed) + p->plane_y * cos(p->rot_Speed);
    }
    if(m->key->LEFT)
    {
        old_dir_x = p->direct_x;
        p->direct_x = p->direct_x * cos(-p->rot_Speed) - p->direct_y * sin(-p->rot_Speed);  // Añadir signo negativo
        p->direct_y = old_dir_x * sin(-p->rot_Speed) + p->direct_y * cos(-p->rot_Speed);
        old_plane_x = p->plane_x;
        p->plane_x = p->plane_x * cos(-p->rot_Speed) -p->plane_y * sin(-p->rot_Speed);
        p->plane_y = old_plane_x * sin(-p->rot_Speed) + p->plane_y * cos(-p->rot_Speed);
    }    
}

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
        rotate_player(m, - diff * sensitivity);
    
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