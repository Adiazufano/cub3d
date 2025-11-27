/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floor_sky_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:45:14 by mparra-s          #+#    #+#             */
/*   Updated: 2025/11/27 16:05:25 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	stablish_floor(t_cubed *cub3d)
{
	int		r;
	int		g;
	int		b;
	int		a;
	char	**splited_format;

	a = 255;
	splited_format = ft_split(cub3d -> floor_format, ',');
	split_size(splited_format, cub3d);
	split_isdigit(splited_format, cub3d);
	r = ft_atoi(splited_format[0]);
	g = ft_atoi(splited_format[1]);
	b = ft_atoi(splited_format[2]);
	cub3d -> floor_color = (b << 8) | (g << 16) | (r << 24) | (a);
	free_split(splited_format);
}

void	stablish_sky(t_cubed *cub3d)
{
	int		r;
	int		g;
	int		b;
	int		a;
	char	**splited_format;

	a = 255;
	splited_format = ft_split(cub3d -> sky_format, ',');
	split_size(splited_format, cub3d);
	split_isdigit(splited_format, cub3d);
	r = ft_atoi(splited_format[0]);
	g = ft_atoi(splited_format[1]);
	b = ft_atoi(splited_format[2]);
	cub3d -> sky_color = (b << 8) | (g << 16) | (r << 24) | (a);
	free_split(splited_format);
}
