/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:25:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/11/25 17:20:26 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*FUNCNION QUE EJECUTA LA TECLA AGACHARSE MODIFICANDO EL POV Y EL PITCH*/
void move_pov(t_map *m)
{
    if(m->player->pitch == 0)
    {
        m->player->pitch = 100;
        m->player->fov = 0.66;
        m->player->speed_ratio = 0.5;
    } 
    else
    {
        m->player->pitch = 0;
        m->player->fov = 0.66;
        m->player->speed_ratio = 1.0;
    }    
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
/* FUNCIÓN QUE CALCULA EL DESPLAZAMIENTO DEL PERSONAJE CADA VEZ 
QUE PRESIONAS UNA TECLA */
void	movement_keys(t_map *m, t_player *p)
{
	p->new_pos_row = p->pos_row;
    p->new_pos_col = p->pos_col;
    
    if(m->key->W)
    {
        p->new_pos_row += p->direct_x * p->mov_Speed;
        p->new_pos_col += p->direct_y * p->mov_Speed;
    }
    if(m->key->S)
    {
        p->new_pos_row -= p->direct_x * p->mov_Speed;
        p->new_pos_col -= p->direct_y * p->mov_Speed;
    }
    if(m->key->D)
    {
        p->new_pos_row -= p->direct_y * p->mov_Speed;
        p->new_pos_col += p->direct_x * p->mov_Speed;
    }
    if(m->key->A)
    {
        p->new_pos_row += p->direct_y * p->mov_Speed;
        p->new_pos_col -= p->direct_x * p->mov_Speed;
    }
}

/* FUNCIÓN PARA DETERMINAR EL MOVIMIENTO DEL PERSONAJE. ESTABLECEMOS CONTROL DE MURO PARA NO CHOCAR*/
void	movement(t_map *m)
{
    t_player *p;
    double diff;
    double margin;
	int sprint;
    
    p = m->player;
	if (p->sprint)
		sprint = 2;
	else
		sprint = 1;
    margin = 0.1;  // Margen de seguridad para no atravesar muros
    p->oldtime = p->time;
    p->time = mlx_get_time();
    diff = p->time - p->oldtime;
    p->mov_Speed = diff * 3.0 * p->speed_ratio * sprint;
    if(p->mov_Speed > 1)
        p->mov_Speed = 1;
    
    movement_keys(m, p);
    rotation(m);
   rotation_mouse(m);
    
    // Comprobar colisión con margen en X (filas)
    if (((m->map[(int)(p->new_pos_row + margin)][(int)p->pos_col] != '1' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1')  &&
        (m->map[(int)(p->new_pos_row - margin)][(int)p->pos_col] != '1' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1')) && ((m->map[(int)(p->new_pos_row + margin)][(int)p->pos_col] != '3' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3')  &&
        (m->map[(int)(p->new_pos_row - margin)][(int)p->pos_col] != '3' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3')))
        p->pos_row = p->new_pos_row;
    
    // Comprobar colisión con margen en Y (columnas)
    if (((m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '1') &&
        (m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1' && m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '1')) && ((m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3' && m->map[(int)p->pos_row][(int)(p->new_pos_col + margin)] != '3') &&
        (m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3' && m->map[(int)p->pos_row][(int)(p->new_pos_col - margin)] != '3')))
        p->pos_col = p->new_pos_col;
}