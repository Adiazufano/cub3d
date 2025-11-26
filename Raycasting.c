/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:54:48 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/26 17:35:36 by aldiaz-u         ###   ########.fr       */
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
		if(m->map[p->map_x][p->map_y] == '1' || m->map[p->map_x][p->map_y] == '3')
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
	p->line_height = (int)(m->height / p->perpWallDist);
	p->init_draw = -p->line_height / 2 + m->height / 2 - p->pitch;  // Usar pitch aquí
	if(p->init_draw < 0)
		p->init_draw = 0;
	p->finish_draw = p->line_height / 2 + m->height / 2 - p->pitch;  // Y aquí
	if(p->finish_draw >= m->height)
		p->finish_draw = m->height - 1;
}

void    init_draw_col(t_tex_bytes *t, t_draw_col *dc, t_map *m, t_player *p)
{
	dc->screen = m->image->pixels;
	dc->screen_w = m->width;
	dc->screen_h = m->height;
	dc->drawStart = p->init_draw;
	dc->drawEnd = p->finish_draw;
	dc->lineHeight = p->line_height;
	dc->side = p->side;
	dc->rayDirX = p->DirrayX;
	dc->rayDirY = p->DirrayY;
	dc->pitch = p->pitch;
	dc->tex = t;
}


void raycasting_draw(t_player *p, t_map *m, int x, t_tex_bytes *tex)
{
	double wallX;
	t_draw_col  dc;

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
	init_draw_col(tex, &dc, m, p);
	dc.x = x;
	dc.wallX = wallX;
	if (dc.screen && dc.tex && dc.lineHeight > 0 && dc.drawStart <= dc.drawEnd)
	{
		draw_textured_column_no_pack(&dc);
		return;
	}
}

t_tex_bytes	*select_texture(t_textures *tetxures, t_map *m, t_player *p)
{
	t_tex_bytes *current;

	current = NULL;
	if (p->side == 0)
	{
		if (p->stepX > 0)
			current = tetxures->north_tetxure;
		else
			current = tetxures->south_texture;
	}
	else
	{
		if (p->stepY > 0)
			current = tetxures->west_texture;
		else
			current = tetxures->east_texture;
	}
	if (p->map_x >= 0 && p->map_x < m->height)
	{
		if (p->map_y >= 0 && p->map_y < (int)ft_strlen(m->map[p->map_x]))
			if (m->map[p->map_x][p->map_y] == '3' && tetxures->door_texture)
				current = tetxures->door_texture;
	}
	return (current);
}

void	raycasting_draw_utils(t_player *p, t_map *m, t_textures *textures)
{
	int	x;
	t_tex_bytes *current;

	x = 0;
	while(x < m->width)
	{
		p->cameraX = (2 * x / (double)m->width) - 1;
		p->DirrayX = p->direct_x + p->plane_x * p->cameraX;
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
		current = select_texture(textures, m, p);
		raycasting_draw(p, m, x, current);
		x++;
	}
}
int raycasting(t_player *p, t_map *m)
{
	static t_textures textures;
	static	int	textures_load;
	// Cargar solo la primera vez
	if (!textures_load)
	{
		textures.north_tetxure = load_texture_bytes(m -> cub3d -> north_texture);
		textures.east_texture = load_texture_bytes(m -> cub3d -> east_texture);
		textures.west_texture = load_texture_bytes(m -> cub3d -> west_texture);
		textures.south_texture = load_texture_bytes(m -> cub3d -> south_texture);
		textures.door_texture = load_texture_bytes(m->cub3d->door_texture);
		textures_load = 1;
	}
	if (!m->image || !m->image->pixels)
		return (0);
	raycasting_draw_utils(p, m, &textures);
	return(1);
}
