/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:23:22 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/12 15:00:54 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


uint32_t *convert_tex_to_uint(mlx_texture_t *tex)
{
    uint32_t    *pixels;
    uint32_t    i;
    
    i = 0;
    if (!tex || !tex->pixels || tex->width <= 0 || tex->height <= 0)
        return NULL;
    pixels = malloc(sizeof(uint32_t) * tex->width * tex->height);
    if (!pixels)
        return NULL;

    while (i < tex->width * tex->height)
    {
        uint8_t r = tex->pixels[i * 4 + 0];
        uint8_t g = tex->pixels[i * 4 + 1];
        uint8_t b = tex->pixels[i * 4 + 2];
        uint8_t a = tex->pixels[i * 4 + 3];
        pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
        i++;
    }
    return pixels;
}

mlx_texture_t *slice_texture(mlx_texture_t *atlas, int x, int y)
{
    // Seguridad
    if (!atlas || x < 0 || y < 0 || FRAMEW <= 0 || FRAMEH <= 0)
        return NULL;

    if ((uint32_t)(x + FRAMEW) > atlas->width ||
        (uint32_t)(y + FRAMEH) > atlas->height)
    {
        printf("Error: slice fuera de los límites del atlas\n");
        return NULL;
    }
    
    int row;
    int col;
    int dest;
    int src;

    row = 0;
    col = 0;
    dest = 0;
    src = 0;
    // Creamos la textura a devolver
    mlx_texture_t *out;
    
    out = malloc(sizeof(mlx_texture_t));
    if (!out)
        return NULL;

    out->width = FRAMEW;
    out->height = FRAMEH;
    out->bytes_per_pixel = 4;
    out->pixels = malloc(FRAMEW * FRAMEH * 4);
    if (!out->pixels)
    {
        free(out);
        return NULL;
    }

    // Copiar píxeles del atlas al slice
    while (row < FRAMEH)
    {
        col = 0;
        while (col < FRAMEW)
        {
            dest = (row * FRAMEW + col) * 4;
            src = ((row + y) * atlas->width + (col + x)) * 4;

            out->pixels[dest + 0] = atlas->pixels[src + 0]; // R
            out->pixels[dest + 1] = atlas->pixels[src + 1]; // G
            out->pixels[dest + 2] = atlas->pixels[src + 2]; // B
            out->pixels[dest + 3] = atlas->pixels[src + 3]; // A
            col++;
        }
        row++;
    }
    return out;
}


/******************************************************************************/
/*    Función donde vamos a cargar el atlas png con todos los sprites         */
/*    del enemigo y vamos a llamar a la función que va a seccionar cada uno   */
/******************************************************************************/

void    seg_walk(t_anim_ene *e)
{
    int i;

    i = 0;
    e->walk_count = 6;
    e->walk[0] = slice_texture(e->atlas, 0, 45);
    e->walk[1] = slice_texture(e->atlas, 287, 45);
    e->walk[2] = slice_texture(e->atlas, 546, 45);
    e->walk[3] = slice_texture(e->atlas, 821, 45);
    e->walk[4] = slice_texture(e->atlas, 1092, 45);
    e->walk[5] = slice_texture(e->atlas, 1365, 45);
    while (i < e->walk_count)
    {
        if (!e->walk[i])
            printf("Warning: seg_walk slice %d == NULL\n", i);
        i++;
    }         
}

void    tex_id(int *src, int count, int *idx)
{
    int i;

    i = 0;
    while (i < count)
    {
        src[i] =  *idx;
        i++;
        (*idx)++;
    }
    
}

void push_text(t_tex_info *dst, mlx_texture_t **src, int count, int capacity)
{
    if (!dst || !src || count <= 0 || capacity <= 0)
    {
        printf("push_text_safe: puntero NULL o count/capacity inválidos\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (!src[i])
        {
            printf("push_text_safe: slice src[%d] == NULL, se omite\n", i);
            continue;
        }

        if (dst->count < 0 || dst->count >= capacity)
        {
            /* Protección: no sobrescribir memoria. */
            printf("push_text_safe: warning - dst->count (%d) fuera de capacidad (%d)\n",
                   dst->count, capacity);
            break;
        }

        dst->widths[dst->count] = src[i]->width;
        dst->heights[dst->count] = src[i]->height;
        dst->pixeles[dst->count] = convert_tex_to_uint(src[i]);

        if (!dst->pixeles[dst->count])
        {
            printf("push_text_safe: convert_tex_to_uint falló en slice %d\n", i);
            exit(1);
        }
        dst->count++;
    }
}

/* --------------------- carga y registro completo --------------------- */

/*
 load_ene_text:
  - carga atlas en e->atlas
  - llama seg_walk/seg_hit/seg_attack/seg_death (tus funciones)
  - crea m->texture_info y convierte todos los slices en pixeles
  - rellena e->*_tex_id con offsets en el array global
  - deja atlas liberado (mlx_delete_texture) porque ya convertimos todo
*/

void load_ene_text(t_anim_ene *e, t_map *m)
{
    if (!e || !m)
        return;

    /* Cargar atlas */
    mlx_texture_t *atlas = mlx_load_png("./textures/Spiderdemon.png");
    if (!atlas)
    {
        printf("Error: fallo al cargar Spiderdemon.png\n");
        exit(1);
    }
    e->atlas = atlas;

    /* Generar slices */
    seg_walk(e);
    int total = e->walk_count;
    if (total <= 0 || total > 1024)
    {
        printf("Error: total frames inválido (%d)\n", total);
        mlx_delete_texture(e->atlas);
        e->atlas = NULL;
        exit(1);
    }

    /* Crear estructura y arrays con inicialización a 0 (muy importante) */
    m->texture_info = malloc(sizeof(t_tex_info));
    if (!m->texture_info) exit(1);
    ft_memset(m->texture_info, 0, sizeof(t_tex_info));

    m->texture_info->pixeles = malloc(sizeof(uint32_t*) * total);
    m->texture_info->widths  = malloc(sizeof(int) * total);
    m->texture_info->heights = malloc(sizeof(int) * total);
    if (!m->texture_info->pixeles || !m->texture_info->widths || !m->texture_info->heights)
    {
        perror("malloc");
        exit(1);
    }
    /* Inicializar a 0 las tablas para evitar lecturas de basura si algo falla */
    for (int i = 0; i < total; ++i)
    {
        m->texture_info->pixeles[i] = NULL;
        m->texture_info->widths[i] = 0;
        m->texture_info->heights[i] = 0;
    }
    m->texture_info->count = 0;

    /* Guardar slices en t_enemy_tex_info */
    m->texture_enemy = malloc(sizeof(t_enemy_tex_info));
    if (!m->texture_enemy) exit(1);
    m->texture_enemy->walk = e->walk;
    m->texture_enemy->walk_count = e->walk_count;

    /* Push seguro: ahora push_text recibe 'capacity' */
    push_text(m->texture_info, e->walk, e->walk_count, total);

    m->n_sprites = m->texture_info->count;

    /* Asignar tex_id (asegúrate de que e->walk_tex_id tenga espacio) */
    int idx = 0;
    tex_id(e->walk_tex_id, e->walk_count, &idx);

    mlx_delete_texture(e->atlas);
    e->atlas = NULL;

    m->tex_width = FRAMEW;
    m->tex_height = FRAMEH;
}

