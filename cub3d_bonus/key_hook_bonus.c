/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:54:26 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/05 15:30:50 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	door(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '3')
		m->map[front_row][front_col] = '2';
	else if (m->map[front_row][front_col] == '2')
		m->map[front_row][front_col] = '3';
}

void	teleport(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '4' && m->portal->close_portal == 1)
	{
		p->pos_row = m->portal->close_player_pos_row + 0.5 + p->direct_y * 1.0;
		p->pos_col = m->portal->close_player_pos_col + 0.5 + p->direct_x * 1.0;
		p->direct_x = m->portal->close_dir_x;
		p->direct_y = m->portal->close_dir_y;
		p->plane_x = m->portal->close_plane_x;
		p->plane_y = m->portal->close_plane_y;
	}
	else if (m->map[front_row][front_col] == '5' && m->portal->open_portal == 1)
	{
		p->pos_row = m->portal->open_player_pos_row + 0.5 + p->direct_y * 1.0;
		p->pos_col = m->portal->open_player_pos_col + 0.5 + p->direct_x * 1.0;
		p->direct_x = m->portal->open_dir_x;
		p->direct_y = m->portal->open_dir_y;
		p->plane_x = m->portal->open_plane_x;
		p->plane_y = m->portal->open_plane_y;
	}
}

void	open_portal(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '1' && m->portal->open_portal == 0)
	{
		m->map[front_row][front_col] = '4';
		m->portal->last_open_pos_r = front_row;
		m->portal->last_open_pos_c = front_col;
		m->portal->open_player_pos_row = p->pos_row;
		m->portal->open_player_pos_col = p->pos_col;
		m->portal->open_dir_x = p->direct_x * -1.0;
		m->portal->open_dir_y = p->direct_y * -1.0;
		m->portal->open_plane_x = p->plane_x * -1.0;
		m->portal->open_plane_y = p->plane_y * -1.0;
		m->portal->open_portal++;
	}
	else if (m->map[front_row][front_col] == '1' && m->portal->open_portal == 1)
	{
		m->map[front_row][front_col] = '4';
		m->map[m->portal->last_open_pos_r][m->portal->last_open_pos_c] = '1';
		m->portal->last_open_pos_r = front_row;
		m->portal->last_open_pos_c = front_col;
		m->portal->open_player_pos_row = p->pos_row;
		m->portal->open_player_pos_col = p->pos_col;
		m->portal->open_dir_x = p->direct_x * -1.0;
		m->portal->open_dir_y = p->direct_y * -1.0;
		m->portal->open_plane_x = p->plane_x * -1.0;
		m->portal->open_plane_y = p->plane_y * -1.0;
	}
}

void	close_portal(t_map *m)
{
	t_player	*p;
	int			front_row;
	int			front_col;

	p = m->player;
	front_row = p->pos_row + p->direct_y * 0.9;
	front_col = p->pos_col + p->direct_x * 0.9;
	if (m->map[front_row][front_col] == '1' && m->portal->close_portal == 0)
	{
		m->map[front_row][front_col] = '5';
		m->portal->last_close_pos_r = front_row;
		m->portal->last_close_pos_c = front_col;
		m->portal->close_player_pos_row = p->pos_row;
		m->portal->close_player_pos_col = p->pos_col;
		m->portal->close_dir_x = p->direct_x * -1.0;
		m->portal->close_dir_y = p->direct_y * -1.0;
		m->portal->close_plane_x = p->plane_x * -1.0;
		m->portal->close_plane_y = p->plane_y * -1.0;
		m->portal->close_portal++;
	}
	else if (m->map[front_row][front_col] == '1' && m->portal->close_portal == 1)
	{
		m->map[front_row][front_col] = '5';
		m->map[m->portal->last_close_pos_r][m->portal->last_close_pos_c] = '1';
		m->portal->last_close_pos_r = front_row;
		m->portal->last_close_pos_c = front_col;
		m->portal->close_player_pos_row = p->pos_row;
		m->portal->close_player_pos_col = p->pos_col;
		m->portal->close_dir_x = p->direct_x * -1.0;
		m->portal->close_dir_y = p->direct_y * -1.0;
		m->portal->close_plane_x = p->plane_x * -1.0;
		m->portal->close_plane_y = p->plane_y * -1.0;
	}
}

void	key_event(mlx_key_data_t key_code, void *param)
{
	t_map	*m;
	int		pressed;
	int		released;

	m = param;
	pressed = (key_code.action == MLX_PRESS || key_code.action == MLX_REPEAT);
	released = (key_code.action == MLX_RELEASE);
	key_move_event(key_code, m);
	if (key_code.key == MLX_KEY_E && key_code.action == MLX_PRESS)
		door(m);
	if (key_code.key == MLX_KEY_C && key_code.action == MLX_PRESS)
		move_pov(m);
	if (key_code.key == MLX_KEY_Q && key_code.action == MLX_PRESS)
		open_portal(m);
	if (key_code.key == MLX_KEY_Z && key_code.action == MLX_PRESS)
		close_portal(m);
	if (key_code.key == MLX_KEY_LEFT_SHIFT)
		m->player->sprint = pressed && !released;
	if (key_code.key == MLX_KEY_LEFT)
		m->key->left = pressed && !released;
	if (key_code.key == MLX_KEY_RIGHT)
		m->key->right = pressed && !released;
	if (key_code.key == MLX_KEY_ESCAPE)
		mlx_close_window(m->mlx);
}

void	key_move_event(mlx_key_data_t key_code, void *param)
{
	t_map	*m;
	int		pressed;
	int		released;

	m = param;
	pressed = (key_code.action == MLX_PRESS || key_code.action == MLX_REPEAT);
	released = (key_code.action == MLX_RELEASE);
	if (key_code.key == MLX_KEY_W)
		m->key->w = pressed && !released;
	if (key_code.key == MLX_KEY_S)
		m->key->s = pressed && !released;
	if (key_code.key == MLX_KEY_A)
		m->key->a = pressed && !released;
	if (key_code.key == MLX_KEY_D)
		m->key->d = pressed && !released;
}

void	rotation_mouse(t_map *m)
{
	static int	first_frame = 1;
	int32_t		mouse_x;
	int32_t		mouse_y;
	double		diff;
	double		sensitivity;

	sensitivity = 0.002;
	mlx_get_mouse_pos(m->mlx, &mouse_x, &mouse_y);
	if (first_frame)
	{
		first_frame = 0;
		mlx_set_cursor_mode(m->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(m->mlx, WIDTH / 2, HEIGHT / 2);
		return ;
	}
	diff = mouse_x - (WIDTH / 2);
	if (fabs(diff) > 1.0)
		rotate_player(m, diff * sensitivity);
	mlx_set_cursor_mode(m->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(m->mlx, WIDTH / 2, HEIGHT / 2);
}

void	rotate_player(t_map *m, double rot)
{
	t_player	*p;
	double		old_dir;
	double		old_plane;

	p = m->player;
	old_dir = p->direct_x;
	p->direct_x = p->direct_x * cos(rot) - p->direct_y * sin(rot);
	p->direct_y = old_dir * sin(rot) + p->direct_y * cos(rot);
	old_plane = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane * sin(rot) + p->plane_y * cos(rot);
}
