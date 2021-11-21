/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:49:19 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:44:28 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_test_textures(char *str)
{
int fd;
int i;

i = 0;
fd = open(str, O_RDONLY, NULL);
if (fd < 1)
{
	close(fd);
	ft_error_msg("Error\ncannot load texture / wrong path");
}
close(fd);
if (str[ft_strlen(str) - i - 1] != 'm' || str[ft_strlen(str) - i - 2] != 'p' || str[ft_strlen(str) - i - 3] != 'x' || str[ft_strlen(str) - i - 4] != '.')
ft_error_msg("Error\nwrong texture format");
}

void ft_error_check(int x, t_mlx *glo)
{
	if (x == 0)
	{
		free(glo);
		exit(1);
	}
}

void ft_error_msg(char *str)
{
	ft_putendl_fd(str, 1);
	exit(1);
}

int ft_check_argc_v(int argc, char *argv[], t_mlx *glo)
{
int x;
if (argc == 1)
ft_error_msg("Error\nno .cub given as arg");
if (argc > 1)
{
x = ft_strlen(argv[1]) - 1;
if (argv[1][x] != 'b')
ft_error_msg("Error\nno .cub given as arg");
if (argv[1][x - 1] != 'u')
ft_error_msg("Error\nno .cub given as arg");
if (argv[1][x - 2] != 'c')
ft_error_msg("Error\nno .cub given as arg");
if (argv[1][x - 3] != '.')
ft_error_msg("Error\nno .cub given as arg");
}
if (argc > 2)
    {
        if (ft_strncmp(argv[2], "--save", 8) == 0)
            glo->save = 1;
		else
			ft_error_msg("Error\nno valid second arg - write --save instead");
    }
if (argc > 3)
ft_error_msg("Error\ntoo many args");
return (x);
}