/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:32:33 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:47:20 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_exit(void)
{
    exit(1);
    return (0);
}

void    ft_orientation_init(t_mlx *glo)
{
if (glo->player_ori == 'N')
{
	glo->dirX = 0;
    glo->dirY = -1;
    glo->planeX = -0.5;
    glo->planeY = 0;
}
if (glo->player_ori == 'W')
    {
    glo->dirX = 1;
    glo->dirY = 0;
    glo->planeX = 0;
    glo->planeY = -0.5;
    }
if (glo->player_ori == 'E')
    {
    glo->dirX = -1;
    glo->dirY = 0;
    glo->planeX = 0;
    glo->planeY = 0.5;
    }
if (glo->player_ori == 'S')
    {
    glo->dirX = 0;
    glo->dirY = 1;
    glo->planeX = 0.5;
    glo->planeY = 0;
    }
    return ;
}

void ft_reset(t_mlx *glo)
{
    glo->posX = glo->posInitX + 0.5;
    glo->posY = glo->posInitY + 0.5;
    glo->dirX = -1;
    glo->dirY = 0;
    glo->planeX = 0;
    glo->planeY = 0.5;
    glo->time = 0;
    glo->oldtime = 0;
    glo->up = 0;
    glo->down = 0;
    glo->right = 0;
    glo->left = 0;
    glo->speed = 0.04;
    glo->latspeed = 0.05;
    glo->move_mouseX = glo->resX / 2;
    glo->move_mouseY = 0;
    glo->ceiling_on = 0;
    if (!(glo->zbuffer = malloc(glo->resX * sizeof(double))))
    ft_error_msg("cannot allocate memory");
    ft_orientation_init(glo);
    textures_init(glo);
}

int main(int argc, char *argv[])
{
    t_mlx *glo;

    if (!(glo = malloc(sizeof(t_mlx))))
        return (0);
    struct_init(glo);   
    ft_check_argc_v(argc, argv, glo); 
    ft_cub_parsing(glo, argv);
    if (ft_parsing(glo) == 0)
    ft_putendl_fd("parsing error\n", 1);
    ft_screen_init(glo);
    ft_reset(glo);
    mlx_hook(glo->win, 17, (1L << 17), ft_exit, glo);
    mlx_hook(glo->win, 2, (1L << 0), key_press, glo);
    mlx_hook(glo->win, 3, (1L << 1), key_release, glo);
    mlx_hook(glo->win, 6, (1L << 6), mouse_capture, glo);
    ft_raycast(glo);
    mlx_loop_hook(glo->mlx_ptr, ft_move, glo);
    mlx_loop(glo->mlx_ptr);
}


void ft_print_map(t_mlx *glo)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < glo->maxX && y <= glo->maxY)
    {
        printf("%i", glo->themap[x][y]);
        x++;
        if (x == glo->maxX)
        {
            y++;
            x = 0;
            printf("\n");
        }
    }
    return;
}