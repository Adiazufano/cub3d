#ifndef		CUB3D_H
#define		CUB3D_H
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/time.h>
#include	"./libft/libft.h"
#include	"get_next_line.h"

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

#endif