/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_textures_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:14:24 by marvin            #+#    #+#             */
/*   Updated: 2025/12/03 17:14:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


/****************************************************************************/
/* Función para liberar las texturas                                        */
/****************************************************************************/

void free_sprite_textures(t_map *m)
{
    int i;

    i = 0;
    if (!m || !m->sprite_textures)
        return ;
    while (i < m->n_sprites)
    {
        free(m->sprite_textures[i]);
        i++;
    }
    free(m->sprite_textures);
    m->sprite_textures = NULL;
    m->n_sprites = 0;
}