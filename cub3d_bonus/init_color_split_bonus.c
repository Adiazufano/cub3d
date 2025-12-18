/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_split_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:52:35 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/18 14:38:58 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	split_size(char **split, t_cubed *cub3d)
{
	int	index;

	index = 0;
	while (split[index])
		index++;
	if (index != 3)
	{
		free_split(split);
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
}

void	split_isdigit(char **split, t_cubed *cub3d)
{
	int	index;
	int	j;

	index = 0;
	while (split[index])
	{
		j = 0;
		while (split[index][j])
		{
			while (split[index][j] == ' ' || split[index][j] == '\t')
				j++;
			if (!ft_isdigit(split[index][j]))
			{
				free_split(split);
				printf("Error: invalid rgb format\n");
				free_cub3d(cub3d);
				exit(1);
			}
			j++;
		}
		index++;
	}
}

int	validate_rgb(t_cubed *cub3d, char *format)
{
	int		r;
	int		g;
	int		b;
	char	**splited_format;

	if (!format)
	{
		printf("Error: missing color\n");
		exit(1);
	}
	validate_commas(format, cub3d);
	splited_format = ft_split(format, ',');
	split_size(splited_format, cub3d);
	split_isdigit(splited_format, cub3d);
	r = ft_atoi(splited_format[0]);
	g = ft_atoi(splited_format[1]);
	b = ft_atoi(splited_format[2]);
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
	{
		printf("Error: invalid rgb format\n");
		free_cub3d(cub3d);
		exit(1);
	}
	free_split(splited_format);
	return (1);
}
