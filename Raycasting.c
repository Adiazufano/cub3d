/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:54:48 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/19 16:31:28 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void raycasting_init(t_player *p)
{                                                 
	p->hit = 0;
	p->map_x = (int)p->pos_row;                                   //Inicializamos la posición del haz en el mapa en el jugador. Debe de estar dentro del bucle para inicializarlo correctamente para haz.
	p->map_y = (int)p->pos_col;
	if(p->DirrayX < 0)
	{
		p->stepX = -1;
		p->side_DistX = (p->pos_row - p->map_x) * p->delta_DistX;
	}
	else
	{
		p->stepX = 1;
		p->side_DistX = (p->map_x - p->pos_row + 1) * p->delta_DistX;
	}
	if(p->DirrayY < 0)
	{
		p->stepY = -1;
		p->side_DistY = (p->pos_col - p->map_y) * p->delta_DistY;
	}
	else
	{
		p->stepY = 1;
		p->side_DistY = (p->map_y - p->pos_col + 1) * p->delta_DistY;
	}     
}

/* FUNCIÓN QUE IMPLEMENTA EL ALGORITMO PARA DETERMINAR DONDE GOLPEA EL HAZ CON LA PARED
	DIGITAL DIFFERENTIAL ANALYZER */

void raycasting_DDA(t_player *p, t_map *m)
{
	while(p->hit == 0)                                  // El bucle se repite mientras no encontremos un muro.
	{
		if(p->side_DistX < p->side_DistY)               // Si cuesta menos recorrer la casilla en horizontal que en vertical.
		{
			p->side_DistX += p->delta_DistX;
			p->map_x += p->stepX;
			p->side = 0;
		}
		else                                            // Si cuesta menos recorrer la casilla en vertical que en horizontal.
		{
			p->side_DistY += p->delta_DistY;
			p->map_y += p->stepY;
			p->side = 1;
		}
		if(m->map[p->map_x][p->map_y] > 0)
			p->hit = 1;                
	}
}

/* FUNCIÓN QUE CALCULA LA DISTANCIA PERPENDICULAR REAL A LA PARED, LA ALTURA DE LA LÍNEA A DIBUJAR Y LOS LÍMITES
	QUE DELIMITAN EL VECTOR VERTICAL */

/* ¿SI ESTABLECEMOS UNA ALTURA A LA MITAD LA PERSEPECTIVA HARÍA QUE PARECIESE QUE EL PERSONAJE ESTÁ AGACHADO?
   ¿Y CON UNA RELACIÓN MAYOR PARECERÍA QUE ESTÁ TUMBADO? */


void raycasting_wall(t_player *p, t_map *m)
{
	if(p->side == 0)                                                // Si el rayo incide horizontalmente restamos la última distancia agregada.
	p->perpWallDist = p->side_DistX - p->delta_DistX;
	else
	p->perpWallDist = p->side_DistY - p->delta_DistY;               // Si el rayo incide verticalmente restamos la última distancia agregada.    
	p->line_height = m->height/p->perpWallDist;
	p->init_draw = (m->height / 2) - (p->line_height / 2);          // Aquí calculamos los límites superior e inferior del muro en función de la perspectiva.
	if(p->init_draw < 0)
		p->init_draw = 0;
	p->finish_draw = (p->line_height / 2) + (m->height / 2);
	if(p->finish_draw > m->height)
		p->finish_draw = m->height - 1;
}


void raycasting_draw(t_player *p, t_map *m, int x)
{
	int y;
	uint32_t color_2 = 0x00FF00FF;
	
	y = 0;
	while(y < m->height)
	{
		if(y >= p->init_draw && y <= p->finish_draw)
			mlx_put_pixel(m->image, x, y, color_2);
		y++;        
	}
}

int raycasting(t_player *p, t_map *m)
{
	int x;
	
	x = 0;
	while(x < m->width)                                             //Con este bucle recorremos la ventana de izquierda a derecha columna por columna
	{
		p->cameraX = (2 * x / (double)m->width) - 1;                //Con esto transformamos la posición de la columna a un valor que determina su posición en el eje horizontal.
		p->DirrayX = p->direct_x + p->plane_x * p->cameraX;         //Con esta fórmula obtienes un vector de dirección diferente para cada columna.
		p->DirrayY = p->direct_y + p->plane_y * p->cameraX;
		if(p->DirrayX == 0)
		p->delta_DistX = 1e30;
		else 
		p->delta_DistX = fabs(1 / p->DirrayX);
		if(p->DirrayY == 0)
		p->delta_DistY = 1e30;
		else 
		p->delta_DistY = fabs(1 / p->DirrayY);
		raycasting_init(p);
		raycasting_DDA(p, m);
		raycasting_wall(p, m);
		raycasting_draw(p, m, x);
		x++;            
	}
	return(1);
}
