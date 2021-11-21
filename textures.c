/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 13:37:41 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/09 17:19:17 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void textures_init(t_mlx *glo)
{
int a;
int b;

a = 64;
b = 64;
glo->textures[0].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_so, &a, &b);
glo->textures[0].data = mlx_get_data_addr(glo->textures[0].img_ptr, &glo->textures[0].bpp, &glo->textures[0].size_l, &glo->textures[0].endian);
glo->textures[1].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_no, &a, &b);
glo->textures[1].data = mlx_get_data_addr(glo->textures[1].img_ptr, &glo->textures[1].bpp, &glo->textures[1].size_l, &glo->textures[1].endian);
glo->textures[2].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_ea, &a, &b);
glo->textures[2].data = mlx_get_data_addr(glo->textures[2].img_ptr, &glo->textures[2].bpp, &glo->textures[2].size_l, &glo->textures[2].endian);
glo->textures[3].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_we, &a, &b);
glo->textures[3].data = mlx_get_data_addr(glo->textures[3].img_ptr, &glo->textures[3].bpp, &glo->textures[3].size_l, &glo->textures[3].endian);
glo->textures[4].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_so, &a, &b);
glo->textures[4].data = mlx_get_data_addr(glo->textures[4].img_ptr, &glo->textures[4].bpp, &glo->textures[4].size_l, &glo->textures[4].endian);
glo->textures[5].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_sprite, &a, &b);
glo->textures[5].data = mlx_get_data_addr(glo->textures[5].img_ptr, &glo->textures[5].bpp, &glo->textures[5].size_l, &glo->textures[5].endian);
glo->textures[6].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_floor, &a, &b);
glo->textures[6].data = mlx_get_data_addr(glo->textures[6].img_ptr, &glo->textures[6].bpp, &glo->textures[6].size_l, &glo->textures[6].endian);
a = 512;
b = 512;
glo->textures[7].img_ptr = mlx_xpm_file_to_image(glo->mlx_ptr, glo->text_ceiling, &a, &b);
glo->textures[7].data = mlx_get_data_addr(glo->textures[7].img_ptr, &glo->textures[7].bpp, &glo->textures[7].size_l, &glo->textures[7].endian);
}

void ft_floor_ceiling_text(t_mlx *glo, int a)
{
	int y;
	int p;
	int x;
	
	y = 0;
	while (++y < glo->resY)
{
	x = 0;
glo->raydirX0 = glo->dirX - glo->planeX;
glo->raydirY0 = glo->dirY - glo->planeY;
glo->raydirX1 = glo->dirX + glo->planeX;
glo->raydirY1 = glo->dirY + glo->planeY;
p = y - glo->resY / 2;
glo->posZ = 0.5 * glo->resY;
glo->rowdistance = glo->posZ / p;
glo->floorstepX = glo->rowdistance * (glo->raydirX1 - glo->raydirX0) / glo->resX;
glo->floorstepY = glo->rowdistance * (glo->raydirY1 - glo->raydirY0) / glo->resX;
glo->floorX = glo->posX + glo->rowdistance * glo->raydirX0;
glo->floorY = glo->posY + glo->rowdistance * glo->raydirY0;
while (++x < glo->resX)
{
glo->cellX = (int)(glo->floorX);
glo->cellY = (int)(glo->floorY);
glo->tx = (int)(64 * (glo->floorX - glo->cellX)) & (63);
glo->ty = (int)(64 * (glo->floorY - glo->cellY)) & (63);
	glo->floorX += glo->floorstepX;
	glo->floorY += glo->floorstepY;
	memcpy(glo->img_data + 4 * glo->resX * y + x * 4, &glo->textures[6].data[glo->ty % 64 * glo->textures[6].size_l + glo->tx % 64 * glo->textures[6].bpp / 8], sizeof(int));
	if (glo->ceiling_on == 1)
	memcpy(glo->img_data + 4 * glo->resX * (glo->resY - y - 1) + x * 4, &glo->textures[1].data[glo->ty % 64 * glo->textures[1].size_l + glo->tx % 64 * glo->textures[1].bpp / 8], sizeof(int));
}
}	
}

void ft_sky(t_mlx *glo)
{
if (glo->ceiling_on == 0)
{
        glo->y = -1;
        if (glo->x < glo->resX && glo->y < glo->resY)
        {
            while (++glo->y < glo->drawstart)
				memcpy(glo->img_data + (4 * glo->resX * glo->y) + (glo->x * 4), &glo->textures[7].data[glo->y % 512 * glo->textures[7].size_l + glo->x % 512 * glo->textures[7].bpp / 8], sizeof(int));
        }
}
}

void ft_sprites(t_mlx *glo)
{
int i;

i = 0;
while (i < glo->sprite_num)
{
glo->sprite_order[i] = i;
glo->sprite_distance[i] = ((glo->posX - glo->sprites[i].x) * (glo->posX - glo->sprites[i].x) + (glo->posY - glo->sprites[i].y) * (glo->posY - glo->sprites[i].y));	
	i++;
}

ft_sort_basic(glo);
ft_sprite_draw(glo);
}

void ft_sort_basic(t_mlx *glo)
{
int i;
i = 0;
double temp;
int temp2;
while (i < glo->sprite_num - 1)
{	
if (glo->sprite_distance[i] < glo->sprite_distance[i + 1])
{
temp = glo->sprite_distance[i];
glo->sprite_distance[i] = glo->sprite_distance[i + 1];
temp2 = glo->sprite_order[i];
glo->sprite_order[i] = glo->sprite_order[i + 1];
glo->sprite_distance[i + 1] = temp;
glo->sprite_order[i + 1] = temp2;
temp = 0;
temp2 = 0;
i = -1;
}
i++;	
}	

/*i = 0;
while (i < glo->sprite_num - 1)
{
printf(" %f\n", glo->sprite_distance[i]);
printf(" %i\n", glo->sprite_order[i]);
i++;
}*/
}

void ft_sprite_draw(t_mlx *glo)
{
int i;
int y;
int d;
int stripe;
int movescreen; 

movescreen = (0 / glo->transformY); /*to move sprites up and down*/
i = 0;
while (i < glo->sprite_num)
{
	/*printf(" sprite_draw_check \n");*/
	glo->spriteX = glo->sprites[glo->sprite_order[i]].x - glo->posX;
	glo->spriteY = glo->sprites[glo->sprite_order[i]].y - glo->posY;
	glo->invDet = 1.0 / (glo->planeX * glo->dirY - glo->dirX * glo->planeY);
	glo->transformX = glo->invDet * (glo->dirY * glo->spriteX - glo->dirX * glo->spriteY);
	glo->transformY = glo->invDet * (-glo->planeY * glo->spriteX + glo->planeX * glo->spriteY);
	glo->spriteScreenX = (int)((glo->resX/ 2) * (1 + glo->transformX / glo->transformY));
	glo->spriteHeight = abs((int)(glo->resY / (glo->transformY)));
	glo->drawstartY = -glo->spriteHeight / 2 + glo->resY / 2 + movescreen;
	if (glo->drawstartY < 0)
	glo->drawstartY = 0;
	glo->drawendY = glo->spriteHeight / 2 + glo->resY / 2 + movescreen;
	if (glo->drawendY >= glo->resY)
	glo->drawendY = glo->resY - 1;
	glo->spriteWidth = abs ((int)(glo->resY / (glo->transformY)));
	glo->drawstartX = -glo->spriteWidth / 2 + glo->spriteScreenX;
	if (glo->drawstartX < 0)
	glo->drawstartX = 0;
	glo->drawendX = glo->spriteWidth / 2 + glo->spriteScreenX;
	if (glo->drawendX >= glo->resX)
	glo->drawendX = glo->resX - 1;
	/*printf("spriteorder[i] = %i [%i] \n", glo->sprite_order[i], i);*/

stripe = glo->drawstartX;
while (stripe < glo->drawendX)
{
	glo->texX = (int)(256 * (stripe - (-glo->spriteWidth / 2 + glo->spriteScreenX)) * 64 / glo->spriteWidth) / 256;
	if (glo->transformY > 0 && stripe > 0 && stripe < glo->resX && glo->transformY < glo->zbuffer[stripe])
	{
		y = glo->drawstartY;
		while (y < glo->drawendY)
		{
			d = (y - movescreen) * 256 - glo->resY * 128 + glo->spriteHeight * 128;
			glo->texY = ((d * 64) / glo->spriteHeight) / 256;
			if ((glo->textures[5].data[glo->texY % 64 * glo->textures[5].size_l + glo->texX % 64 * glo->textures[5].bpp / 8]) != 0)
			memcpy(glo->img_data + 4 * glo->resX * y + stripe * 4, &glo->textures[5].data[glo->texY % 64 * glo->textures[5].size_l + glo->texX % 64 * glo->textures[5].bpp / 8], sizeof(int));
			y++;
		}
	}
	stripe++;
}
i++;
}
}