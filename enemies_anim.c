/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:23:22 by mparra-s          #+#    #+#             */
/*   Updated: 2025/12/05 15:35:15 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t *convert_tex_to_uint(mlx_texture_t *tex)
{
    uint32_t    *pixels;
    uint32_t    i;
    
    i = 0;
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

mlx_texture_t *slice_texture_hit(mlx_texture_t *atlas, int x, int y)
{
    // Seguridad
    if (!atlas || x < 0 || y < 0 || FRAMEHITW <= 0 || FRAMEHITH <= 0)
        return NULL;

    if ((uint32_t)(x + FRAMEHITW) > atlas->width ||
        (uint32_t)(y + FRAMEHITH) > atlas->height)
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

    out->width = FRAMEHITW;
    out->height = FRAMEHITH;
    out->bytes_per_pixel = 4;
    out->pixels = malloc(FRAMEHITW * FRAMEHITH * 4);
    if (!out->pixels)
    {
        free(out);
        return NULL;
    }

    // Copiar píxeles del atlas al slice
    while (row < FRAMEHITH)
    {
        while (col < FRAMEHITW)
        {
            dest = (row * FRAMEHITW + col) * 4;
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
    e->walk_count = 30;
    e->walk[0] = slice_texture(e->atlas, 0, 45);
    e->walk[1] = slice_texture(e->atlas, 287, 45);
    e->walk[2] = slice_texture(e->atlas, 546, 45);
    e->walk[3] = slice_texture(e->atlas, 821, 45);
    e->walk[4] = slice_texture(e->atlas, 1092, 45);
    e->walk[5] = slice_texture(e->atlas, 1365, 45);    
    e->walk[6] = slice_texture(e->atlas, 0, 180);
    e->walk[7] = slice_texture(e->atlas, 279, 180);
    e->walk[8] = slice_texture(e->atlas, 552, 180);
    e->walk[9] = slice_texture(e->atlas, 818, 180);
    e->walk[10] = slice_texture(e->atlas, 1092, 180);
    e->walk[11] = slice_texture(e->atlas, 1365, 180);        
    e->walk[12] = slice_texture(e->atlas, 0, 310);
    e->walk[13] = slice_texture(e->atlas, 275, 310);
    e->walk[14] = slice_texture(e->atlas, 546, 310);
    e->walk[15] = slice_texture(e->atlas, 820, 310);
    e->walk[16] = slice_texture(e->atlas, 1100, 310);
    e->walk[17] = slice_texture(e->atlas, 1375, 310);        
    e->walk[18] = slice_texture(e->atlas, 0, 442);
    e->walk[19] = slice_texture(e->atlas, 280, 442);
    e->walk[20] = slice_texture(e->atlas, 546, 442);
    e->walk[21] = slice_texture(e->atlas, 820, 442);
    e->walk[22] = slice_texture(e->atlas, 1095, 442);
    e->walk[23] = slice_texture(e->atlas, 1368, 442);    
    e->walk[24] = slice_texture(e->atlas, 0, 575);
    e->walk[25] = slice_texture(e->atlas, 280, 575);
    e->walk[26] = slice_texture(e->atlas, 549, 575);
    e->walk[27] = slice_texture(e->atlas, 820, 575);
    e->walk[28] = slice_texture(e->atlas, 1090, 575);
    e->walk[29] = slice_texture(e->atlas, 1366, 575);        
}

void    seg_hit(t_anim_ene *e)
{
    e->hit_count = 8;
    e->hit[0] = slice_texture_hit(e->atlas, 13, 740);
    e->hit[1] = slice_texture_hit(e->atlas, 254, 740);
    e->hit[2] = slice_texture_hit(e->atlas, 503, 740);
    e->hit[3] = slice_texture_hit(e->atlas, 748, 740);
    e->hit[4] = slice_texture_hit(e->atlas, 990, 740);
    e->hit[5] = slice_texture_hit(e->atlas, 1234, 740);    
    e->hit[6] = slice_texture_hit(e->atlas, 1475, 740);
    e->hit[7] = slice_texture_hit(e->atlas, 1720, 740);    
}

void    seg_attack(t_anim_ene *e)
{
    e->attack_count = 10;
    e->attack[0] = slice_texture(e->atlas, 1732, 45);
    e->attack[1] = slice_texture(e->atlas, 2000, 45);
    e->attack[2] = slice_texture(e->atlas, 1732, 178);
    e->attack[3] = slice_texture(e->atlas, 2008, 178);
    e->attack[4] = slice_texture(e->atlas, 1739, 312);
    e->attack[5] = slice_texture(e->atlas, 2010, 312);    
    e->attack[6] = slice_texture(e->atlas, 1739, 442);
    e->attack[7] = slice_texture(e->atlas, 2010, 442);
    e->attack[8] = slice_texture(e->atlas, 1735, 575);    
    e->attack[9] = slice_texture(e->atlas, 2008, 740);  
}

void    seg_death(t_anim_ene *e)
{
    e->death_count = 10;
    e->death[0] = slice_texture_hit(e->atlas, 0, 920);
    e->death[1] = slice_texture_hit(e->atlas, 230, 920);
    e->death[2] = slice_texture_hit(e->atlas, 460, 920);
    e->death[3] = slice_texture_hit(e->atlas, 700, 920);
    e->death[4] = slice_texture_hit(e->atlas, 930, 920);
    e->death[5] = slice_texture_hit(e->atlas, 1165, 920);    
    e->death[6] = slice_texture_hit(e->atlas, 1390, 920);
    e->death[7] = slice_texture_hit(e->atlas, 1625, 920);
    e->death[8] = slice_texture_hit(e->atlas, 1855, 920);    
    e->death[9] = slice_texture_hit(e->atlas, 200, 920);  
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

void    push_text(t_tex_info *dst, mlx_texture_t **src, int count)
{
    int i;
    
    i = 0;
    if (!dst || !src)
        return ;
    while (i < count)
    {
        
        dst->pixeles[dst->count] = convert_tex_to_uint(src[i]);
        dst->widths[dst->count] = src[i]->width;
        dst->heights[dst->count] = src[i]->height;
        if(!dst->pixeles[dst->count])
            exit (1);
        dst->count++;
        i++;
    }
}
void    load_ene_text2(t_enemy_tex_info *e, t_tex_info *tex_info)
{
    int total;

    

    tex_info->count = 0;
    push_text(tex_info, e->walk, e->walk_count);
    push_text(tex_info, e->hit, e->hit_count);
    push_text(tex_info, e->attack, e->attack_count);
    push_text(tex_info, e->death, e->death_count);
}

void    load_ene_text(t_anim_ene *e, t_map *m)
{
    mlx_texture_t *atlas;
    int total;
    int i;
    int idx;
    
    i = 0;
    idx = 0;
    atlas = mlx_load_png("./textures/Spiderdemon.png");
    e->atlas = atlas;
    if (!e->atlas)
    {
        printf("Error: failed to load Spiderdemon atlas\n");
        exit (1);
    }
    seg_walk(e);
    seg_hit(e);
    seg_attack(e);
    seg_death(e);
    
    total = e->walk_count + e->hit_count + e->attack_count + e->death_count;
    if (total <= 0)
        return ;
    m->texture_info = malloc(sizeof(t_tex_info));
    if (!m->texture_info)
    {
        printf("Error: malloc texture_info\n");
        exit(1);
    }
    m->texture_info->pixeles = malloc (sizeof(uint32_t*) * total);
    m->texture_info->widths = malloc (sizeof(int) * total);
    m->texture_info->heights = malloc (sizeof(int) * total);
    if (!m->texture_info->pixeles || m->texture_info->widths || m->texture_info->heights)
    {
        printf("Error: malloc texture_arrays\n");
        exit(1);        
    }
    m->texture_info->count = 0;
    
    /* Crear (y rellenar) estructura t_enemy_tex_info dentro de m que apunte a tus slices */
    m->texture_enemy = malloc(sizeof(t_enemy_tex_info));
    if (!m->texture_enemy)
    {
        printf("Error: malloc texture_enemy\n");
        exit(1);
    }
    m->texture_enemy->walk = e->walk;
    m->texture_enemy->walk_count = e->walk_count;
    m->texture_enemy->hit = e->hit;
    m->texture_enemy->hit_count = e->hit_count;
    m->texture_enemy->attack = e->attack;
    m->texture_enemy->attack_count = e->attack_count;
    m->texture_enemy->death = e->death;
    m->texture_enemy->death_count = e->death_count;

    /* Convertir y empujar en el mismo orden que usarás los tex_id */
    push_text(m->texture_info, e->walk, e->walk_count);
    push_text(m->texture_info, e->hit, e->hit_count);
    push_text(m->texture_info, e->attack, e->attack_count);
    push_text(m->texture_info, e->death, e->death_count);

    m->n_sprites = m->texture_info->count;
    /* Asignar tex_id arrays dentro de e (índices en el array global) */
    /* Inicializamos idx a 0 y rellenamos los tex_id para cada grupo */
    idx = 0;
    tex_id(e->walk_tex_id, e->walk_count, &idx);
    tex_id(e->hit_tex_id, e->hit_count, &idx);
    tex_id(e->attack_tex_id, e->attack_count, &idx);
    tex_id(e->death_tex_id, e->death_count, &idx);

    /* (Opcional) asigna a m->tex_width/tex_height los valores por defecto si los usas en otras partes */
    m->tex_width = FRAMEW;
    m->tex_height = FRAMEH;
}

