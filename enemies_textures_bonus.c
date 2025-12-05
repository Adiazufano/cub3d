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

//void free_sprite_textures(t_map *m)
//{
//    int i;
//
//    i = 0;
//    if (!m || !m->sprite_textures)
//        return ;
//    while (i < m->n_sprites)
//    {
//        free(m->sprite_textures[i]);
//        i++;
//    }
//    free(m->sprite_textures);
//    m->sprite_textures = NULL;
//    m->n_sprites = 0;
//}

/* Libera un slice mlx_texture_t creado por slice_texture/slice_texture_hit */
void free_mlx_slice(mlx_texture_t *t)
{
    if (!t)
        return;
    if (t->pixels)
        free(t->pixels);
    free(t);
}

void free_texture_info(t_map *m)
{
    int i;

    if (!m || !m->texture_info)
        return;
    for (i = 0; i < m->texture_info->count; ++i)
    {
        if (m->texture_info->pixeles[i])
            free(m->texture_info->pixeles[i]);
    }
    free(m->texture_info->pixeles);
    free(m->texture_info->widths);
    free(m->texture_info->heights);
    free(m->texture_info);
    m->texture_info = NULL;
    m->n_sprites = 0;
}

void free_enemy_slices(t_anim_ene *e)
{
    int i;

    if (!e)
        return;
    for (i = 0; i < 30; ++i)
    {
        if (e->walk[i])
            free_mlx_slice(e->walk[i]), e->walk[i] = NULL;
    }
    for (i = 0; i < 8; ++i)
    {
        if (e->hit[i])
            free_mlx_slice(e->hit[i]), e->hit[i] = NULL;
    }
    for (i = 0; i < 10; ++i)
    {
        if (e->attack[i])
            free_mlx_slice(e->attack[i]), e->attack[i] = NULL;
    }
    for (i = 0; i < 10; ++i)
    {
        if (e->death[i])
            free_mlx_slice(e->death[i]), e->death[i] = NULL;
    }
    /* atlas si queda -> liberar */
    if (e->atlas)
    {
        mlx_delete_texture(e->atlas);
        e->atlas = NULL;
    }
}

/* wrapper de liberación total (llamar al terminar el programa) */
void free_all_enemy_textures(t_anim_ene *e, t_map *m)
{
    if (m)
        free_texture_info(m);
    if (e)
        free_enemy_slices(e);
}