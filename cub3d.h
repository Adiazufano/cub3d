/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:12:00 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 12:27:51 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include "./libft/libft.h"
# include "get_next_line.h"
# include <math.h>
# include "MLX42/MLX42.h"
# define WIDTH 640
# define HEIGHT 480
# define TEXTWIDTH 64
# define TEXTHEIGHT 64
# define MAPWIDTH 4
# define MAPHEIGHT 24

typedef struct s_cub3d
{
	uint32_t	sky_color;
	uint32_t	floor_color;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_format;
	char		*door_texture;
	char		*sky_format;
	char		**map;
}	t_cubed;

typedef struct point
{
	size_t	max_w;
	size_t	rows;
	int		x;
	int		y;
	int		start_x;
	int		start_y;
}	t_point;

typedef struct s_player
{
	double	pos_row;
	double	pos_col;
	double	direct_x;
	double	direct_y;
	double	plane_x;
	double	plane_y;
	double	fov;
	double	camera_x;
	double	dirray_x;
	double	dirray_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	time;
	double	oldtime;
	double	mov_speed;
	double	rot_speed;
	double	pitch;
	double	speed_ratio;
	double	new_pos_row;
	double	new_pos_col;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		init_draw;
	int		finish_draw;
	int		sprint;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_map
{
	t_player	*player;
	t_cubed		*cub3d;
	t_keys		*key;
	mlx_image_t	*image;
	char		**map;
	char		orientation;
	void		*mlx;
	int			width;
	int			height;
}	t_map;

typedef struct s_tex
{
	uint8_t	*pixels;
	int		width;
	int		height;
	int		channels;
}	t_tex_bytes;

typedef struct s_draw_col
{
	t_tex_bytes	*tex;
	uint8_t		*screen;
	double		wallx;
	double		ray_dir_x;
	double		ray_dir_y;
	double		pitch;
	int			screen_w;
	int			screen_h;
	int			x;
	int			draw_start;
	int			draw_end;
	int			side;
	int			line_height;
}	t_draw_col;

typedef struct s_tex_ctx
{
	int64_t	step;
	int		tex_w;
	int		tex_h;
	int		channels;
	int		tex_x;
	int		fb_stride;
}	t_tex_ctx;

typedef struct s_textures
{
	t_tex_bytes	*north_tetxure;
	t_tex_bytes	*south_texture;
	t_tex_bytes	*west_texture;
	t_tex_bytes	*east_texture;
	t_tex_bytes	*door_texture;
}	t_textures;

t_tex_bytes	*load_texture_bytes(const char *path);
t_tex_bytes	*select_texture(t_textures *tetxures, t_map *m, t_player *p);
void		add_textures(char *line, t_cubed *cub3d);
void		add_formats(char *line, t_cubed *cub3d);
void		map_err(char *line, int *j, t_cubed *cub3d, int fd);
void		add_map(char *line, t_cubed *cub3d, int fd, int *j);
void		free_cub3d(t_cubed *cub3d);
void		empty_line_err(t_cubed *cub3d, int fd);
void		validate_texture_path(char *path, t_cubed *cub3d);
void		free_split(char **split);
void		validate_commas(char *format, t_cubed *cub3d);
void		split_size(char **split, t_cubed *cub3d);
void		split_isdigit(char **split, t_cubed *cub3d);
void		validate_formats(t_cubed *cub3d);
void		validate_textures(t_cubed *cub3d);
void		add_to_cub3d(int fd, t_cubed *cub3d);
void		run_flood_check(t_cubed *cub3d);
void		initialize(t_player *p, t_map *m, t_cubed *cub3d);
void		initialize_direction(t_player *p, t_map *m);
void		game_loop(void *param);
void		setup_window(t_map *m);
void		raycasting_init(t_player *p);
void		raycasting_dda(t_player *p, t_map *m);
void		raycasting_wall(t_player *p, t_map *m);
void		raycasting_draw(t_player *p, t_map *m, int x, t_tex_bytes *tex);
void		raycasting_draw_utils(t_player *p, t_map *m, t_textures *textures);
void		draw_textured_column_no_pack(t_draw_col *p);
void		rotate_player(t_map *m, double rot);
void		rotation_mouse(t_map *m);
void		rotate_player(t_map *m, double rot);
void		movement(t_map *m);
void		move_pov(t_map *m);
void		key_event(mlx_key_data_t key_code, void *param);
void		rotation(t_map *m);
void		rotation_mouse(t_map *m);
void		paint_minimap(t_map *m);
void		check_n_players(t_cubed *cub3d);
void		width_and_height(t_cubed *cub3d, t_point *start);
void		get_start_pos(t_cubed *cub3d, t_point *start);
void		init_flood_filll(t_point *start);
void		run_flood_check(t_cubed *cub3d);
void		paint_minimap_c(t_map *m, int x, int y);
void		paint_minimap_3(t_map *m, int x, int y, int a);
void		paint_minimap_0(t_map *m, int x, int y, int a);
void		paint_minimap_1(t_map *m, int x, int y, int a);
void		mov_colision(t_map *m, t_player *p);
void		key_move_event(mlx_key_data_t key_code, void *param);
void		free_exit(t_cubed *cub3d);
void		normalize_map_h(t_cubed *cub3d, size_t w, size_t maxw, size_t i);
void		print_cubed(t_cubed *cub3d);
void		add_to_cub3d(int fd, t_cubed *cub3d);
void		validate_textures(t_cubed *cub3d);
void		validate_formats(t_cubed *cub3d);
void		validate_commas(char *format, t_cubed *cub3d);
void		add_formats(char *line, t_cubed *cub3d);
void		map_err(char *line, int *j, t_cubed *cub3d, int fd);
void		empty_line_err(t_cubed *cub3d, int fd);
void		free_split(char **split);
void		free_cub3d(t_cubed *cub3d);
void		split_isdigit(char **split, t_cubed *cub3d);
void		split_size(char **split, t_cubed *cub3d);
void		init_cubed(t_cubed *cub3d);
void		add_to_cub3d(int fd, t_cubed *cub3d);
void		print_cubed(t_cubed *cub3d);
void		stablish_sky(t_cubed *cub3d);
void		add_formats(char *line, t_cubed *cub3d);
void		stablish_floor(t_cubed *cub3d);
void		validate_commas(char *format, t_cubed *cub3d);
void		normalize_map(t_cubed *cub3d);
void		normalize_map_h(t_cubed *cub3d, size_t w, size_t maxw, size_t i);
void		add_map(char *line, t_cubed *cub3d, int fd, int *j);
void		init_draw_cl(t_tex_bytes *t, t_draw_col *dc, t_map *m, t_player *p);
void		check_n_players(t_cubed *cub3d);
void		width_and_height(t_cubed *cub3d, t_point *start);
void		free_partial_visited(int **visited, int n);
void		init_flood_filll(t_point *start);
void		free_visited(int **visited, int rows);
char		*get_textures_path(char *s);
int			alloc_visited(int ***out, t_point *start, t_cubed *cub3d);
int			add_map_line(t_cubed **cub3d, const char *line);
int			count_commas(t_cubed *cub3d, char *format);
int			validate_rgb(t_cubed *cub3d, char *format);
int			init_cube(t_map *m, t_cubed *cub3d);
int			raycasting(t_player *p, t_map *m);
int			flood_expand(t_point *pos, char **map, int **visited);
int			flood_rec(t_point *start_pos, char **map, int **visited);
int			get_height(t_map *m);
int			get_width(t_map *m);
int			init_program(t_cubed *cub3d, t_map *m, int fd);
int			add_new_map(t_cubed **cub3d, char *dup, size_t n);
int			count_commas(t_cubed *cub3d, char *format);
int			validate_rgb(t_cubed *cub3d, char *format);
int			add_map_line(t_cubed **cub3d, const char *line);
int			add_new_map(t_cubed **cub3d, char *dup, size_t n);
int			raycasting(t_player *p, t_map *m);

#endif
