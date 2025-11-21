/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:54:26 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/21 15:08:27 by aldiaz-u         ###   ########.fr       */
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
    
    p = m->player;
    p->oldtime = p->time;
    p->time = mlx_get_time();                       //Calculamos el tiempo en el momento para hacer un movimiento fluido.
    diff = p->time - p->oldtime;                    //Diferencial de tiempo entre llamadas para que el movimiento sea fluido.
    p->mov_Speed = diff * 3.0;
    if(p->mov_Speed > 0.1)
        p->mov_Speed = 0.1;
    new_pos_row = p->pos_row;                       //Guardamos la posición actual para después, actualizarla si no hace que vayamos a cruzar un muro.
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
            new_pos_row += p->direct_y * p->mov_Speed;
            new_pos_col -= p->direct_x * p->mov_Speed;        
    }
    if(m->key->A)
    {
            new_pos_row -= p->direct_y * p->mov_Speed;
            new_pos_col += p->direct_x * p->mov_Speed;        
    }
    rotation(m);
    rotation_mouse(m);
    if(m->map[(int)new_pos_row][(int)p->pos_col] == 0)                  //Comprobamos si vamos a atravesar un muro y si no, actualizamos la posición.              
        p->pos_row = new_pos_row;
    if(m->map[(int)p->pos_row][(int)new_pos_col] == 0)
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
        p->direct_x = p->direct_x * cos(-p->rot_Speed) - p->direct_y * sin(-p->rot_Speed);
        p->direct_y = old_dir_x * sin(-p->rot_Speed) + p->direct_y * cos(-p->rot_Speed);
        old_plane_x = p->plane_x;
        p->plane_x = p->plane_x * cos(-p->rot_Speed) -p->plane_y * sin(-p->rot_Speed);
        p->plane_y = old_plane_x * sin(-p->rot_Speed) + p->plane_y * cos(-p->rot_Speed);
    }
    if(m->key->LEFT)
    {
        old_dir_x = p->direct_x;
        p->direct_x = p->direct_x * cos(p->rot_Speed) - p->direct_y * sin(p->rot_Speed);
        p->direct_y = old_dir_x * sin(p->rot_Speed) + p->direct_y * cos(p->rot_Speed);
        old_plane_x = p->plane_x;
        p->plane_x = p->plane_x * cos(p->rot_Speed) -p->plane_y * sin(p->rot_Speed);
        p->plane_y = old_plane_x * sin(p->rot_Speed) + p->plane_y * cos(p->rot_Speed);
    }    
}

void rotation_mouse(t_map *m)
{
    t_player *p;
    int32_t old_dir_x;
    int32_t old_dir_y;
    double diff;
    double sensitivity;

    p = m->player;
    sensitivity = 0.002; 
    mlx_get_mouse_pos(m->mlx, &old_dir_x, &old_dir_y);
    diff = old_dir_x - (WIDTH / 2);
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
    p->plane_x = p->plane_x * cos(rot) - p->direct_y * sin(rot);
    p->plane_y = old_plane * sin(rot) + p->direct_y * cos(rot);
}