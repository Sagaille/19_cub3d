/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:19:09 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:49:25 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_charac_check(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        while (s[i] == ' ' || s[i] == '\t' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
        i++;
        if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != 'N' && s[i] != 'S' && s[i] != 'W' && s[i] != 'O' && s[i] != 'E' && s[i] != '\n')
        ft_error_msg("Error\nWrong character inside map\n");
        i++;
    }
    return (1);
}

void ft_count(char *str, t_mlx *glo)
{
    int i;
    int t;
    i = 0;

    glo->maxX = 0;
    glo->maxY = 0;
    t = 0;
    while (str[i])
    {
        if (str[0] == '\n')
            i++;
        while (str[i] && str[i] != '\n')
        {
            i++;
            t++;
        }
        if (t >= glo->maxX)
            glo->maxX = t;
        t = 0;
        glo->maxY++;
        i++;
    }
    return ;
}

int ft_str_to_array(t_mlx *glo)
{
    int i;
    int x;
    int y;

    glo->player_ori = '0';
    glo->player_numb = 0;
    i = 0;
    x = 0;
    y = 0;
    if (!(glo->themap = (int**)malloc((glo->maxX) * sizeof(int *))))
       ft_error_msg("Error\ncannot allocate memory\n");
    while (i < glo->maxX)
    {
        if (!(glo->themap[i] = (int*)malloc((glo->maxY) * sizeof(int))))
        ft_error_msg("Error\ncannot allocate memory\n");
        i++;
    }
    i = 0;
    if (!(glo->soluce = malloc((glo->maxX) * sizeof(int *))))
    ft_error_msg("Error\ncannot allocate memory\n");
    while (i < glo->maxX)
    {
        if (!(glo->soluce[i] = malloc((glo->maxY + 1) * sizeof(int))))
        ft_error_msg("Error\ncannot allocate memory\n");
        i++;
    }
    while (x <=  glo->maxX && y <= glo->maxY)
    {
        glo->soluce[glo-> maxX - 1 - x][y] = 0;
        glo->themap[glo-> maxX - 1 - x][y] = 3;
        x++;
        if (x == glo->maxX)
        {
            y++;
            x = 0;
        }
    }
    x = 0;
    y = 0;
    i = 0;
    while (glo->map_str[i])
    {
        while (glo->map_str[i] == '\n')
        {
            y++;
            i++;
            x = 0;
        }
        if (glo->map_str[i] == '1' || glo->map_str[i] == '0' || glo->map_str[i] == '2' || glo->map_str[i] == '3')
        glo->themap[glo->maxX - 1 - x][y] = glo->map_str[i] - 48;
        if (glo->map_str[i] == 'N' || glo->map_str[i] == 'W' || glo->map_str[i] == 'S' || glo->map_str[i] == 'E')
        {
            if (glo->player_numb >= 1)
            ft_error_msg("Error\nMultiple players \n");
            glo->player_ori = glo->map_str[i];
            glo->posInitX = glo-> maxX - 1 - x;
            glo->posInitY = y;
            glo->themap[glo->maxX - 1 - x][y] = 0;
            glo->player_numb++;
        }
        if (glo->map_str[i] == '2')
        {
            glo->sprites[glo->sprite_num].x = (glo->maxX - 1 - x) + 0.5;
            glo->sprites[glo->sprite_num].y = y + 0.5;
            glo->sprite_num++;
            glo->themap[glo->maxX - 1 - x][y] = 0;
        }
        i++;
        x++;
    }
    if (glo->player_numb == 0)
    ft_error_msg("Error\nNo player \n");
    return (1);
}

int ft_parsing(t_mlx *glo)
{
    ft_error_check(ft_charac_check(glo->map_str), glo);
    ft_count(glo->map_str, glo);
    ft_str_to_array(glo);
    ft_backtrack_filler(glo->posInitX, glo->posInitY, glo);
    if (ft_find_map_hole(glo) == 1)
    return (1);
    return (0);
}
