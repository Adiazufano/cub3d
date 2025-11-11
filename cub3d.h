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

#endif