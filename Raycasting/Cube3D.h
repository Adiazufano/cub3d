/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:23:18 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/18 11:28:59 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLX42/MLX42.h>

# define WIDTH 640
# define HEIGHT 480
# define mapwidth 4
# define mapheight 24

typedef struct s_player
{
    double pos_x;           //Posición en el mapa.
    double pos_y;           
    double direct_x;        //Dirección del jugador.
    double direct_y;  
    double plane_x;         //Plano de la cámara.
    double plane_y;
    double fov;
    double cameraX;         //Coordenada-x en el plano de la cámara.
    double DirrayX;         //Dirección del rayo en el eje X;
    double DirrayY;         //Dirección del rayo en el eje Y;
    double side_DistX;      //Distancia que tiene que viajar el rayo desde la posición inicial hasta atravesar el primer limite horizontal de la cuadrícula.
    double side_DistY;      //Distancia que tiene que viajar el rayo desde la posición inicial hasta atravesar el primer limite vertical de la cuadrícula.
    double delta_DistX;     //Distancia que recorre el rayo para atravesar horizontalmente una casilla.
    double delta_DistY;     //Distancia que recorre el rayo para atravesar verticalmente una casilla.
    double perpWallDist;    //Distancia perpendicular al plano de la cámara.
    double time;            //Cálculo del tiempo para el cálculo de los FPS.
    double oldtime;
    int map_x;              //Posición del rayo en el mapa según lo va recorriendo.
    int map_y;
    int stepX;              //Variable que va a determinar el ritmo al que avanza el haz en el eje X.
    int stepY;              //Variable que va a determinar el ritmo al que avanza el haz en el eje Y.
    int hit;                //Variable que comprobará si hemos golpeado un muro o no.
    int side;               //Valor del lado en el que golpea el haz.
    int line_height;        //Altura del muro.
    int init_draw;          //Donde inicia a pintar el muro.
    int finish_draw;        //Donde termina de pintar el muro.
}   t_player;


typedef struct s_map
{
    t_player *player;
    char orientation;   //Orientación a la que empieza el personaje.
    int width;          //Nunca puede ser double.
    int height;         
    int map[mapwidth][mapheight];         //Mapa.
    void    *mlx;
    void    *image;    
}   t_map;

void initialize(t_player *p, t_map *m);
void initialize_direction(t_player *p, t_map *m);


#endif