/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:54:48 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/21 19:27:15 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void raycasting_init(t_player *p)
{                                                  //Quitar;
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
		if(m->map[p->map_x][p->map_y] == '1')
			p->hit = 1;                
	}
}

/* FUNCIÓN QUE CALCULA LA DISTANCIA PERPENDICULAR REAL A LA PARED, LA ALTURA DE LA LÍNEA A DIBUJAR Y LOS LÍMITES
	QUE DELIMITAN EL VECTOR VERTICAL */

/* ¿SI ESTABLECEMOS UNA ALTURA A LA MITAD LA PERSEPECTIVA HARÍA QUE PARECIESE QUE EL PERSONAJE ESTÁ AGACHADO?
   ¿Y CON UNA RELACIÓN MAYOR PARECERÍA QUE ESTÁ TUMBADO? */


void raycasting_wall(t_player *p, t_map *m)
{
	double		draw_start;
	double		draw_end;

    if(p->side == 0)                                                // Si el rayo incide horizontalmente restamos la última distancia agregada.
        p->perpWallDist = p->side_DistX - p->delta_DistX;
    else
        p->perpWallDist = p->side_DistY - p->delta_DistY;               // Si el rayo incide verticalmente restamos la última distancia agregada.
    if (p->perpWallDist <= 1e-6)
        p->perpWallDist = 1e-6;
    p->line_height = (int)(m->height / p->perpWallDist);
    draw_start = -p->line_height / 2 + (m->height / 2);
    draw_end = (p->line_height / 2) + m->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= m -> height)
		draw_end = m->height - 1;
	p -> init_draw = draw_start;
	p -> finish_draw = draw_end;
}


void raycasting_draw(t_player *p, t_map *m, int x, t_tex_bytes *tex)
{
    double wallX;
    int		y;

    if (p->side == 0)
        wallX = p->pos_col + p->perpWallDist * p->DirrayY;
    else
        wallX = p->pos_row + p->perpWallDist * p->DirrayX;
    if (!isfinite(wallX))
        wallX = 0.0;
    else
    {
        wallX -= floor(wallX);
        if (wallX < 0.0) wallX += 1.0;
    }
    uint8_t *screen = (uint8_t*)m->image->pixels;
    if (screen && tex)
    {
        draw_textured_column_no_pack(screen, m->width, m->height,
            x, p->init_draw, p->finish_draw, p->line_height,
            tex, wallX, p->side, p->DirrayX, p->DirrayY);
        return;
    }
    y = p->init_draw;
    while (y <= p->finish_draw && y < m->height)
    {
        mlx_put_pixel(m->image, x, y, 0x00FF00FF);
        y++;
    }
}

int raycasting(t_player *p, t_map *m)
{
	int x;
	t_tex_bytes *north_tetxure;
	t_tex_bytes *east_tetxure;
	t_tex_bytes *weast_tetxure;
	t_tex_bytes *south_tetxure;

	north_tetxure = load_texture_bytes(m -> cub3d -> north_texture);
	east_tetxure = load_texture_bytes(m -> cub3d -> east_texture);
	weast_tetxure = load_texture_bytes(m -> cub3d -> west_texture);
	south_tetxure = load_texture_bytes(m -> cub3d -> south_texture);
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
		  /* load texture bytes per column is expensive; caller should cache textures.
			  as a minimal change we load once before loop in the next iteration */
		  t_tex_bytes *current = north_tetxure;
		  if (p->side == 0)
		  {
			if (p->stepX > 0)
				current = east_tetxure;
			else
				current = weast_tetxure;
		  }
		  else
		  {
			if (p->stepY > 0)
				current = south_tetxure;
			else
				current = north_tetxure;
		  }
		  raycasting_draw(p, m, x, current);
		x++;
	}
	if (north_tetxure)
		free(north_tetxure->pixels), free(north_tetxure);
	if (south_tetxure)
		free(south_tetxure -> pixels), free(south_tetxure);
	if (east_tetxure)
		free(east_tetxure->pixels), free(east_tetxure);
	if (weast_tetxure)
		free(weast_tetxure->pixels), free(weast_tetxure);
	return(1);
}
