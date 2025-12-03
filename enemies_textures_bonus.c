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

/******************************************************************************/
/* Esta función copia y, si es necesario, convierte el orden de canales.      */
/******************************************************************************/

static void conv_tex_pixels(mlx_texture_t *tex, uint32_t *out_buf, int w, int h)
{
    int i;

    i = 0;
    uint32_t *texpixels = (uint32_t *)tex->pixels;
    while (i < w * h)
    {
        uint32_t c = texpixels[i];
        uint8_t a = (c >> 24) & 0xFF;
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = (c >> 0) & 0xFF;
        out_buf[i] = (a << 24) | (r << 16) | (g << 8) | b;
        i++;
    }
}

/***************************************************************************/
/* Carga una textura PNG guarda el buffer en m->sprite_textures[index].    */
/*   Devuelve 0 en éxito, -1 en fallo.                                     */
/***************************************************************************/

int load_sprite_texture_mlx(t_map *m, const char *path, int index)
{
    if (!m || !path || index < 0 || index >= m->n_sprites)
        return -1;

    mlx_texture_t *tex = mlx_load_png(path);
    if (!tex)
        return -1;
    /* Verificación dimensiones */
    if ((int)tex->width != m->tex_width || (int)tex->height != m->tex_height)
    {
        mlx_delete_texture(tex);
        return -1;
    }
    uint32_t *buf = malloc(sizeof(uint32_t) * m->tex_width * m->tex_height);
    if (!buf)
    {
        mlx_delete_texture(tex);
        return -1;
    }
    /* Convertir*/
    conv_tex_pixels(tex, buf, m->tex_width, m->tex_height);
    m->sprite_textures[index] = buf;
    mlx_delete_texture(tex);
    return (0);
}

/****************************************************************************/
/* Inicializa el array de texturas (llamar antes de cargar)                 */
/****************************************************************************/

int init_sprite_textures(t_map *m, int n_textures, int tex_w, int tex_h)
{
    if (!m || n_textures <= 0) return -1;
    m->n_sprites = n_textures;
    m->tex_width = tex_w;
    m->tex_height = tex_h;

    m->sprite_textures = malloc(sizeof(uint32_t *) * n_textures);
    if (!m->sprite_textures) return -1;

    for (int i = 0; i < n_textures; ++i)
        m->sprite_textures[i] = NULL;

    return 0;
}

/****************************************************************************/
/* Función para liberar las texturas                                        */
/****************************************************************************/

void free_sprite_textures(t_map *m)
{
    if (!m || !m->sprite_textures) return;
    for (int i = 0; i < m->n_sprites; ++i)
        free(m->sprite_textures[i]);
    free(m->sprite_textures);
    m->sprite_textures = NULL;
    m->n_sprites = 0;
}