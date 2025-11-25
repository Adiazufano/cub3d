/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:01:18 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/25 09:01:41 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* FUNCIÓN QUE EJECUTA LA TECLA AGACHARSE MODIFICANDO EL POV Y EL PITCH */

void	move_pov(t_map *m)
{
	if (m->player->pitch == 0)
	{
		m->player->pitch = 150;
		m->player->fov = 0.8;
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

void	rotation(t_map *m)
{
	t_player	*p;
	double	old_dir_x;
	double	old_plane_x;

	p = m->player;
	if (m->key->RIGHT)
	{
		old_dir_x = p->direct_x;
		p->direct_x = p->direct_x * cos(-p->rot_Speed)
			- p->direct_y * sin(-p->rot_Speed);
		p->direct_y = old_dir_x * sin(-p->rot_Speed)
			+ p->direct_y * cos(-p->rot_Speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-p->rot_Speed)
			-p->plane_y * sin(-p->rot_Speed);
		p->plane_y = old_plane_x * sin(-p->rot_Speed)
			+ p->plane_y * cos(-p->rot_Speed);
	}
	if (m->key->LEFT)
	{
		old_dir_x = p->direct_x;
		p->direct_x = p->direct_x * cos(p->rot_Speed)
			- p->direct_y * sin(p->rot_Speed);
		p->direct_y = old_dir_x * sin(p->rot_Speed)
			+ p->direct_y * cos(p->rot_Speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(p->rot_Speed)
			-p->plane_y * sin(p->rot_Speed);
		p->plane_y = old_plane_x * sin(p->rot_Speed)
			+ p->plane_y * cos(p->rot_Speed);
	}
}

/* FUNCIÓN QUE CALCULA EL DESPLAZAMIENTO DEL PERSONAJE CADA VEZ 
QUE PRESIONAS UNA TECLA */

void	movement_keys(t_map *m, t_player *p)
{
	p->new_pos_row = p->pos_row;                                        /*Guardamos la posición actual para después, actualizarla si no hace que vayamos a cruzar un muro*/
	p->new_pos_col = p->pos_col;
	if (m->key->W)
	{
		p->new_pos_row += p->direct_x * p->mov_Speed;
		p->new_pos_col += p->direct_y * p->mov_Speed;
	}
	if (m->key->S)
	{
		p->new_pos_row -= p->direct_x * p->mov_Speed;
		p->new_pos_col -= p->direct_y * p->mov_Speed;
	}
	if (m->key->D)
	{
		p->new_pos_row += p->direct_y * p->mov_Speed;
		p->new_pos_col -= p->direct_x * p->mov_Speed;
	}
	if (m->key->A)
	{
		p->new_pos_row -= p->direct_y * p->mov_Speed;
		p->new_pos_col += p->direct_x * p->mov_Speed;
	}
}

/* FUNCIÓN PARA DETERMINAR EL MOVIMIENTO DEL PERSONAJE. ESTABLECEMOS CONTROL DE MURO PARA NO CHOCAR*/

void	movement(t_map *m)
{
	t_player	*p;
	double	diff;
	int	sprint;

	p = m->player;
	if (p->sprint)                                                  /*Esta línea define la velocidad del sprint en función de si presionamos o no la tecla SHIFT_LEFT*/
        sprint = 2;
    else
        sprint = 1;
    p->oldtime = p->time;
	p->time = mlx_get_time();                                       /*Calculamos el tiempo en el momento para hacer un movimiento fluido.*/
	diff = p->time - p->oldtime;                                    /*Diferencial de tiempo entre llamadas para que el movimiento sea fluido.*/
	p->mov_Speed = diff * 3 * p->speed_ratio * sprint;
	if (p->mov_Speed > 1)
		p->mov_Speed = 1;
	movement_keys(m, p);
	rotation(m);
	rotation_mouse(m);
	if (m->map[(int)p->new_pos_row][(int)p->pos_col] == 0 || m->map[(int)p->new_pos_row][(int)p->pos_col] == 2)           /*Comprobamos si vamos a atravesar un muro y si no, actualizamos la posición.*/
		p->pos_row = p->new_pos_row;
	if (m->map[(int)p->pos_row][(int)p->new_pos_col] == 0 || m->map[(int)p->new_pos_row][(int)p->pos_col] == 2)
		p->pos_col = p->new_pos_col;
}
