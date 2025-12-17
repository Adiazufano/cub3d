/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val_formats_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:42:38 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/15 11:59:46 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	validate_formats(t_cubed *cub3d)
{
	if ((validate_rgb(cub3d, cub3d -> floor_format)) == 1)
		stablish_floor(cub3d);
	if ((validate_rgb(cub3d, cub3d -> sky_format)) == 1)
		stablish_sky(cub3d);
}

void	validate_textures(t_cubed *cub3d)
{
	validate_texture_path(cub3d -> north_texture, cub3d);
	validate_texture_path(cub3d -> south_texture, cub3d);
	validate_texture_path(cub3d -> east_texture, cub3d);
	validate_texture_path(cub3d -> west_texture, cub3d);
	validate_texture_path(cub3d -> door_texture, cub3d);
	validate_texture_path(cub3d -> open_portal_texture, cub3d);
	validate_texture_path(cub3d -> close_portal_texture, cub3d);
}

int	count_commas(t_cubed *cub3d, char *format)
{
	int	index;
	int	j;
	int	commas;

	index = 0;
	j = 0;
	commas = 0;
	while (format[index])
	{
		if (format[index] == ',')
		{
			commas++;
			j = index + 1;
			while (format[j] == ' ' || format[j] == '\t')
				j++;
			if (format[j] == ',' || format[j] == '\0')
			{
				printf("Error: invalid rgb format\n");
				free_cub3d(cub3d);
				exit(1);
			}
		}
		index++;
	}
	return (commas);
}

void	validate_commas(char *format, t_cubed *cub3d)
{
	int	index;
	int	commas;

	index = 0;
	while (format[index] == ' ' || format[index] == '\t')
		index++;
	if (format[index] == ',' || format[index] == '\0')
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
	commas = count_commas(cub3d, format);
	if (commas != 2)
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
}

void	add_formats(char *line, t_cubed *cub3d)
{
	if (line[0] == 'F')
	{
		free(cub3d -> floor_format);
		cub3d -> floor_format = ft_strdup(line + 1);
	}
	else if (line[0] == 'C')
	{
		free(cub3d -> sky_format);
		cub3d -> sky_format = ft_strdup(line + 1);
	}
}
