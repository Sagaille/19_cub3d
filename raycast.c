/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:53:53 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 18:04:54 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_screen_init(t_mlx *glo)
{
    int x;
    int y;
    
    if (!(glo->mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    mlx_get_screen_size(glo->mlx_ptr, &x, &y);  //doesnt work on MacOS
    if (x < glo->resX || y < glo->resY)
    ft_error_msg("resolution is too high");
    if (!(glo->win = mlx_new_window(glo->mlx_ptr, glo->resX, glo->resY, "CUBE_3D")))
        return (EXIT_FAILURE);
    return (0);
}

void ft_raycast(t_mlx *glo)
{
    glo->x = -1;
    glo->img = mlx_new_image(glo->mlx_ptr, glo->resX, glo->resY);
    glo->img_data = (int *)mlx_get_data_addr(glo->img, &glo->bpp, &glo->size_l,
                                             &glo->endian);
    ft_floor_ceiling_text(glo, glo->x);
    while (++glo->x < glo->resX)
    {
        ft_raycast_init(glo, glo->x);
        glo->lineHeight = (int)glo->resY / glo->perpWallDist;
        glo->drawstart = (-glo->lineHeight / 2) + (glo->resY / 2);
        if (glo->drawstart < 0)
            glo->drawstart = 0;
        glo->drawend = (glo->lineHeight / 2) + (glo->resY / 2);
        if (glo->drawend >= glo->resY)
            glo->drawend = glo->resY - 1;
        glo->zbuffer[glo->x] = glo->perpWallDist;
        ft_draw_walls(glo->x, glo->drawstart - 1, glo->drawend, glo);
        ft_sky(glo);
        /*ft_draw_floor_ceiling(glo, glo->x);*/
    }
    ft_sprites(glo);
    if (glo->save == 1)
    {
        ft_sprites(glo);
        bmp_generator(glo);
        exit(1);
        glo->save++;
    }
    mlx_put_image_to_window(glo->mlx_ptr, glo->win, glo->img, 0, 0);
    mlx_destroy_image(glo->mlx_ptr, glo->img);
}

void ft_raycast_init(t_mlx *glo, int x)
{

    glo->cameraX = 2 * x / (double)(glo->resX)-1;
    glo->ray_posX = glo->posX;
    glo->ray_posY = glo->posY;
    glo->rayDirX = glo->dirX + glo->planeX * glo->cameraX;
    glo->rayDirY = glo->dirY + glo->planeY * glo->cameraX;
    glo->mapX = (int)glo->ray_posX;
    glo->mapY = (int)glo->ray_posY;
    ft_dda_init(glo);
    ft_dda(glo);
    if (glo->side == 0)
        glo->perpWallDist = (glo->mapX - glo->ray_posX + (1 - glo->stepX) / 2) / glo->rayDirX;
    else
        glo->perpWallDist = (glo->mapY - glo->ray_posY + (1 - glo->stepY) / 2) / glo->rayDirY;
}

void ft_dda_init(t_mlx *glo)
{
    glo->deltaDistY = sqrt(1 + ((glo->rayDirX * glo->rayDirX) / (glo->rayDirY * glo->rayDirY)));
    glo->deltaDistX = sqrt(1 + ((glo->rayDirY * glo->rayDirY) / (glo->rayDirX * glo->rayDirX)));

    if (glo->rayDirX < 0)
    {
        glo->stepX = -1;
        glo->sideDistX = (glo->ray_posX - glo->mapX) * glo->deltaDistX;
    }
    else
    {
        glo->stepX = 1;
        glo->sideDistX = (glo->mapX + 1.0 - glo->ray_posX) * glo->deltaDistX;
    }
    if (glo->rayDirY < 0)
    {
        glo->stepY = -1;
        glo->sideDistY = (glo->ray_posY - glo->mapY) * glo->deltaDistY;
    }
    else
    {
        glo->stepY = 1;
        glo->sideDistY = (glo->mapY + 1.0 - glo->ray_posY) * glo->deltaDistY;
    }
}

/*
    Digital Differential Analysis
    Algo to check where the ray hits the wall
*/
void ft_dda(t_mlx *glo)
{
    glo->hit = 0;
    while (glo->hit == 0)
    {
        if (glo->sideDistX < glo->sideDistY)
        {
            glo->sideDistX += glo->deltaDistX;
            glo->mapX += glo->stepX;
            glo->side = 0;
        }
        else
        {
            glo->sideDistY += glo->deltaDistY;
            glo->mapY += glo->stepY;
            glo->side = 1;
        }
        if (glo->themap[glo->mapX][glo->mapY] > 0)
            glo->hit = 1;
    }
}

void ft_draw_floor_ceiling(t_mlx *glo, int x)
{
    if (glo->drawstart > 0)
    {
        glo->color = 0x4FC3F7;
        glo->y = -1;
        if (x < glo->resX && glo->y < glo->resY)
        {
            while (++glo->y < glo->drawstart)
                memcpy(glo->img_data + 4 * glo->resX * glo->y + x * 4, &glo->color, sizeof(int));
        }
    }
    if (glo->drawend > 0)
    {
        glo->color = 0x729C69;
        glo->y = glo->drawend - 1;
        if (x < glo->resX && glo->y < glo->resY)
        {
            while (++glo->y < glo->resY)
                memcpy(glo->img_data + 4 * glo->resX * glo->y + x * 4, &glo->color, sizeof(int));
        }
    }
}

void ft_draw_walls(int x, int start, int end, t_mlx *glo)
{
    glo->text_num = glo->themap[glo->mapX][glo->mapY];
    if (glo->side == 0)
        glo->wallX = glo->ray_posY + glo->perpWallDist * glo->rayDirY;
    else
        glo->wallX = glo->ray_posX + glo->perpWallDist * glo->rayDirX;
    glo->texX = (int)(glo->wallX * 64);
    if (glo->side == 0 && glo->rayDirX > 0)
        glo->texX = 64 - glo->texX - 1;
    if (glo->side == 1 && glo->rayDirY < 0)
        glo->texX = 64 - glo->texX - 1;
    glo->texX = abs(glo->texX);

    while (++start <= end)
        ft_pixel_into_img(glo, x, start, glo->color);
}

void ft_pixel_into_img(t_mlx *glo, int x, int y, int color)
{
    if (x < glo->resX && y < glo->resY)
    {
        glo->texY = abs((((y * 256 - glo->resY * 128 + glo->lineHeight * 128) * 64) / glo->lineHeight) / 256);
        /* Do we hit a NSWE wall? */
        if (glo->side == 0 && glo->rayDirX < 0)
            memcpy(glo->img_data + 4 * glo->resX * y + x * 4, &glo->textures[2].data[glo->texY % 64 * glo->textures[2].size_l + glo->texX % 64 * glo->textures[2].bpp / 8], sizeof(int)); //east
        if (glo->side == 0 && glo->rayDirX > 0)
            memcpy(glo->img_data + 4 * glo->resX * y + x * 4, &glo->textures[3].data[glo->texY % 64 * glo->textures[3].size_l + glo->texX % 64 * glo->textures[3].bpp / 8], sizeof(int)); //west
        if (glo->side == 1 && glo->rayDirY < 0)
            memcpy(glo->img_data + 4 * glo->resX * y + x * 4, &glo->textures[1].data[glo->texY % 64 * glo->textures[1].size_l + glo->texX % 64 * glo->textures[1].bpp / 8], sizeof(int)); //north
        if (glo->side == 1 && glo->rayDirY > 0)
            memcpy(glo->img_data + 4 * glo->resX * y + x * 4, &glo->textures[0].data[glo->texY % 64 * glo->textures[0].size_l + glo->texX % 64 * glo->textures[0].bpp / 8], sizeof(int));//south
    }
}
