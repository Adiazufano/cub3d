/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:32:06 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/12/12 12:40:53 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_block(char c)
{
	return (c == '1' || c == '3' || c == '4' || c == '5');
}

char	map_at(t_map *m, int r, int c)
{
	int	len;

	if (!m || !m->map || r < 0 || c < 0)
		return ('1');
	if (m->map[r] == NULL)
		return ('1');
	len = 0;
	while (m->map[r][len])
		len++;
	if (c >= len)
		return ('1');
	return (m->map[r][c]);
}
