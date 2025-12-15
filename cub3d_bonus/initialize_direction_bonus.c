/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_direction_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:26:00 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 19:26:37 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	initialize_direction(t_player *p, t_map *m)
{
	if (m->orientation == 'N')
	{
		p->direct_x = 0.0;
		p->direct_y = -1.0;
	}
	if (m->orientation == 'S')
	{
		p->direct_x = 0.0;
		p->direct_y = 1.0;
	}
	if (m->orientation == 'W')
	{
		p->direct_x = -1.0;
		p->direct_y = 0.0;
	}
	if (m->orientation == 'E')
	{
		p->direct_x = 1.0;
		p->direct_y = 0.0;
	}
}
