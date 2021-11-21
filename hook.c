/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:00:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:47:01 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int key_press(int keycode, t_mlx *glo)
{
	if (keycode == 53 || keycode == 65307)
		exit(1);
	if (keycode == 13 || keycode == 119)
		glo->up = 1;
	if (keycode == 1 || keycode == 115)
		glo->down = 1;
	if (keycode == 123 || keycode == 65361)
		glo->left = 1;
	if (keycode == 124 || keycode == 65363)
		glo->right = 1;
	if (keycode == 0 || keycode == 97)
		glo->strafe_l = 1;	
	if (keycode == 2 || keycode == 100)
		glo->strafe_r = 1;
	if (keycode == 122 || keycode == 65470)
		ft_reset(glo);
	return (1);
}

int key_release(int keycode, t_mlx *glo)
{
	if (keycode == 13 || keycode == 119)
		glo->up = 0;
	if (keycode == 1 || keycode == 115)
		glo->down = 0;
	if (keycode == 123 || keycode == 65361)
		glo->left = 0;
	if (keycode == 124 || keycode == 65363)
		glo->right = 0;
	if (keycode == 0 || keycode == 97)
		glo->strafe_l = 0;	
	if (keycode == 2 || keycode == 100)
		glo->strafe_r = 0;
	if ((keycode == 120 || keycode == 65471) && glo->ceiling_on == 1)
		{
			glo->ceiling_on = 0;
			return 1;
		}
	if ((keycode == 120 || keycode == 65471) && glo->ceiling_on == 0)
		glo->ceiling_on = 1;
	
	return (1);
}

int button_press(int button, int x, int y, t_mlx *glo)
{
	printf("button = %i\n", button);
	/*while (x > 0 && x < glo->resX && y > 0 && y > glo->resY)*/
	printf(" x = %i & y = %i\n", x, y);
	return 0;
}

int mouse_capture(int x, int y, t_mlx *glo)
{
/*printf(" x = %i & y = %i\n", x, y);*/
glo->move_mouseX = x;
glo->move_mouseY = y;
return 0;
}

int ft_move(t_mlx *glo)
{
	ft_move_side(glo);
	if (glo->up == 1)
	{
		if (glo->themap[(int)(glo->posX + glo->dirX * glo->speed)][(int)glo->posY] == 0)
			glo->posX += glo->dirX * glo->speed;
		if (glo->themap[(int)(glo->posX)][(int)(glo->posY + glo->dirY * glo->speed)] == 0)
			glo->posY += glo->dirY * glo->speed;
	}
	if (glo->down == 1)
	{
		if (glo->themap[((int)(glo->posX - glo->dirX * glo->speed))][(int)glo->posY] == 0)
			glo->posX -= glo->dirX * glo->speed;
		if (glo->themap[((int)(glo->posX))][((int)(glo->posY + glo->dirY * glo->speed))] == 0)
			glo->posY -= glo->dirY * glo->speed;
	}
	
	ft_raycast(glo);
	return (0);
}

void ft_move_side(t_mlx *glo)
{
	if (glo->right == 1)
	{
		glo->old_dirX = glo->dirX;
		glo->dirX = glo->dirX * cos(-0.05) - glo->dirY * sin(-0.05);
		glo->dirY = glo->old_dirX * sin(-0.05) + glo->dirY * cos(-0.05);
		glo->old_planeX = glo->planeX;
		glo->planeX = glo->planeX * cos(-0.05) - glo->planeY * sin(-0.05);
		glo->planeY = glo->old_planeX * sin(-0.05) + glo->planeY * cos(-0.05);
	}
	if (glo->left == 1)
	{
		glo->old_dirX = glo->dirX;
		glo->dirX = glo->dirX * cos(0.05) - glo->dirY * sin(0.05);
		glo->dirY = glo->old_dirX * sin(0.05) + glo->dirY * cos(0.05);
		glo->old_planeX = glo->planeX;
		glo->planeX = glo->planeX * cos(0.05) - glo->planeY * sin(0.05);
		glo->planeY = glo->old_planeX * sin(0.05) + glo->planeY * cos(0.05);
	}
	if (glo->strafe_r == 1)
	{
		if (glo->themap[(int)(glo->posX + glo->planeX * glo->speed)][(int)glo->posY] == 0)
			glo->posX += glo->planeX * glo->speed;
		if (glo->themap[(int)(glo->posX)][(int)(glo->posY + glo->planeY * glo->speed)] == 0)
			glo->posY += glo->planeY * glo->speed;
	}
	if (glo->strafe_l == 1)
	{
		if (glo->themap[(int)(glo->posX - glo->planeX * glo->speed)][(int)glo->posY] == 0)
			glo->posX -= glo->planeX * glo->speed;
		if (glo->themap[(int)(glo->posX)][(int)(glo->posY + glo->planeY * glo->speed)] == 0)
			glo->posY -= glo->planeY * glo->speed;
	}
	ft_move_mouse(glo);
}

void ft_move_mouse(t_mlx *glo)
{
float speed;

speed = 0;

if (glo->move_mouseX < (glo->resX / 2) - 80)
speed = 0.01;
if (glo->move_mouseX < (glo->resX / 2) - 200)
speed = 0.02;
if (glo->move_mouseX < (glo->resX / 2) - 300)
speed = 0.03;
if (glo->move_mouseX < (glo->resX / 2) - 400)
speed = 0.05;
if (glo->move_mouseX > (glo->resX / 2) + 80)
speed = -0.01;
if (glo->move_mouseX > (glo->resX / 2) + 200)
speed = -0.02;
if (glo->move_mouseX > (glo->resX / 2) + 300)
speed = -0.03;
if (glo->move_mouseX > (glo->resX / 2) + 400)
speed = -0.05;
glo->old_dirX = glo->dirX;
		glo->dirX = glo->dirX * cos(speed) - glo->dirY * sin(speed);
		glo->dirY = glo->old_dirX * sin(speed) + glo->dirY * cos(speed);
		glo->old_planeX = glo->planeX;
		glo->planeX = glo->planeX * cos(speed) - glo->planeY * sin(speed);
		glo->planeY = glo->old_planeX * sin(speed) + glo->planeY * cos(speed);
}
