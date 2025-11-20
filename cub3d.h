#ifndef		CUB3D_H
#define		CUB3D_H
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/time.h>
#include	"./libft/libft.h"
#include	"get_next_line.h"
#include 	<math.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	<stdio.h>
#include 	"MLX42/MLX42.h"
# define WIDTH 640
# define HEIGHT 480
# define mapwidth 4
# define mapheight 24

typedef struct	s_cub3d
{
	char*	north_texture;
	char*	south_texture;
	char*	west_texture;
	char*	east_texture;
	char*	floor_format;
	char*	sky_format;
	char**	map;
}				t_cubed;

typedef struct point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_player
{
    double pos_row;           //Posición en el mapa.
    double pos_col;           
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
    double mov_Speed;
    double rot_Speed;
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
    void    *mlx;
    void    *image;
    char    **map;
    t_cubed *cub3d;
}   t_map;

void	init_cub3d(t_cubed *cub3d);
void	print_cub3d(t_cubed *cub3d);
int		add_map_line(t_cubed **cub3d, const char *line);
void	free_cub3d(t_cubed *cub3d);
char	*get_textures_path(char *s);
void	add_textures(char *line, t_cubed *cub3d);
void	add_formats(char *line, t_cubed *cub3d);
void	map_err(char *line, int *j, t_cubed *cub3d, int fd);
void	add_map(char *line, t_cubed *cub3d, int fd, int *j);
void	empty_line_err(t_cubed *cub3d, int fd);
void	validate_texture_path(char *path, t_cubed *cub3d);
void	free_split(char **split);
int		count_commas(t_cubed *cub3d, char *format);
void	validate_commas(char *format, t_cubed *cub3d);
void	split_size(char **split, t_cubed *cub3d);
void	split_isdigit(char **split, t_cubed *cub3d);
void	validate_rgb(t_cubed *cub3d, char *format);
void	validate_formats(t_cubed *cub3d);
void	validate_textures(t_cubed *cub3d);
void	add_to_cub3d(int fd, t_cubed *cub3d);
void	run_flood_check(t_cubed *cub3d);
void initialize(t_player *p, t_map *m, t_cubed *cub3d);
void initialize_direction(t_player *p, t_map *m);
void game_loop(void *param);
void setup_window(t_map *m);
int init_cube(t_map *m, t_cubed *cub3d);
int raycasting(t_player *p, t_map *m);
void raycasting_init(t_player *p);
void raycasting_DDA(t_player *p, t_map *m);
void raycasting_wall(t_player *p, t_map *m);
void raycasting_draw(t_player *p, t_map *m, int x);


#endif