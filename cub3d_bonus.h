/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:12:00 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 14:49:10 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../get_next_line.h"
# include <math.h>
# include "MLX42/MLX42.h"
# define WIDTH 640
# define HEIGHT 480
# define TEXTWIDTH 64
# define TEXTHEIGHT 64
# define MAPWIDTH 4
# define MAPHEIGHT 24
# define FRAMEW	270
# define FRAMEH	120
# define ENEMY_FRAME_TICKS 4   // velocidad de animación (4 ticks por frame)

typedef struct s_enemy
{
	struct s_enemy	*next;
	double			pos_x;
	double			pos_y;
	double			dx;
	double			dy;
	double			transform_x;
	double			transform_y;
	double			enemy_distance;
	int				anim_frame;
	int				e_walk_count;
	int				e_walk_tex_id;
	int				screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				life;
	int				tex_id;
	double 			last_x;
	double 			last_y;
	double			speed;
}	t_enemy;

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
	char		*open_portal_texture;
	char		*close_portal_texture;
	char		**map;
	t_enemy		*enemy;
}	t_cubed;

typedef struct s_anim_ene
{
	mlx_texture_t	*atlas;
	mlx_texture_t	*walk[6];
	int				walk_tex_id[6];
	int				walk_count;		
} t_anim_ene;

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
	int		*buffer_col;
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

typedef struct s_portal
{
	int		last_open_pos_r;
	int		last_open_pos_c;
	int		last_close_pos_r;
	int		last_close_pos_c;
	int		open_portal;
	int		close_portal;
	double	close_player_pos_row;
	double	close_player_pos_col;
	double	open_player_pos_row;
	double	open_player_pos_col;
	double	open_dir_x;
	double	open_dir_y;
	double	open_plane_x;
	double	open_plane_y;
	double	close_dir_x;
	double	close_dir_y;
	double	close_plane_x;
	double	close_plane_y;
}				t_portal;

typedef struct s_tex_info
{
	uint32_t	**pixeles;
	int			*widths;
	int			*heights;
	int			count;	
} t_tex_info;

typedef struct s_enemy_tex_info
{
	mlx_texture_t	**walk;
	int				walk_count;
}	t_enemy_tex_info;

typedef struct s_map
{
	t_player			*player;
	t_cubed				*cub3d;
	t_keys				*key;
	t_tex_info			*texture_info;
	t_enemy_tex_info 	*texture_enemy;
	t_anim_ene			*e_text;
	t_enemy				*enemy;
	mlx_image_t			*image;
	char				**map;
	char				orientation;
	void				*mlx;
	int					width;
	int					height;
	int					tex_width;
	int					tex_height;
	int					n_sprites;
	t_portal			*portal;
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
	t_tex_bytes	*open_portal_texture;
	t_tex_bytes	*close_portal_texture;
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
void		initialize_bonus(t_player *p, t_map *m, t_cubed *cub3d,
				t_portal *portal);
void		initialize_direction(t_player *p, t_map *m);
void		game_loop(void *param);
void		setup_window(t_map *m);
void		raycasting_init(t_player *p);
void		raycasting_dda(t_player *p, t_map *m);
void		raycasting_wall(t_player *p, t_map *m, int x);
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
int			raycasting_enemy(t_player *p, t_enemy **enemy, t_map *m);
void		paint_sword(t_map *m);
void		teleport(t_map *m);
char		map_at(t_map *m, int r, int c);
int			is_block(char c);
void		door(t_map *m);
void		open_portal(t_map *m);
void		close_portal(t_map *m);
void		free_list(t_enemy *zombie);
void		lstadd_back_ene(t_enemy **lst, t_enemy *new);
t_enemy		*init_enemy(int col, int row);
void		check_n_enemies(t_enemy *enemies, t_cubed *cub3d);
void		load_ene_text(t_anim_ene *e, t_map *m);
#endif
