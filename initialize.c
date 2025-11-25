/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:27:01 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/24 15:53:49 by mparra-s         ###   ########.fr       */
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

void	initialize(t_player *p, t_map *m)
{
	m->orientation = 'N';
	m->height = HEIGHT;
	m->width = WIDTH;
	p->pos_row = 8;                               /*Posición en el mapa. Cuando tenga el mapa introducir una posición correcta.*/
	p->pos_col = 14;
	p->fov = 0.66;
	p->time = 0;                                    //Tiempo del frame actual.
	p->oldtime = 0;                                 //Tiempo del frame antiguo.
	p->mov_Speed = 0.05;                            //Velocidad de movimiento para que sea fluido.
	p->rot_Speed = 0.03;
	p->pitch = 0;
	p->speed_ratio = 1;
	p->sprint = 1;
	p->time = mlx_get_time();
	initialize_direction(p, m);
	p->plane_x = p->direct_y * p->fov;             //Tiene que ser negativo para representar que sea perpendicular al eje de visión.
	p->plane_y = -p->direct_x * p->fov;
}

/* Dirección del jugador. No puede ser 0.0 ya que eso haría que el cálculo de trazado de rayos fuese erroneo */

void	initialize_direction(t_player *p, t_map *m)
{
	if (m->orientation == 'N')
	{
		p->direct_x = -1.0;
		p->direct_y = 0.0;
	}
	if (m->orientation == 'S')
	{
		p->direct_x = 1.0;
		p->direct_y = 0.0;
	}
	if (m->orientation == 'W')
	{
		p->direct_x = 0.0;
		p->direct_y = -1.0;
	}
	if (m->orientation == 'E')
	{
		p->direct_x = 0.0;
		p->direct_y = 1.0;
	}
}

int	init_cube(t_map *m)
{
	m->player = malloc(sizeof (t_player));
	if (!m->player)
		return (0);
	m->key = malloc(sizeof (t_keys));
	if (!m->key)
		return (0);
	memset(m->key, 0, sizeof (t_keys));
	m->mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!m->mlx)
	{
		write(2, "Error: Imposible to create MLX\n", 32);
		return (0);
	}
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	if (!m->mlx || !m->image)
	{
		write(2, "Error: Imposible to create the image\n", 38);
		return (0);
	}
	initialize(m->player, m);
	initialize_map(m);
	return (1);
}
