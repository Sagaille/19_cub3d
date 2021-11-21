/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:13:51 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/11 00:14:24 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void struct_init(t_mlx *glo)
{
glo->resX = 0;
glo->resY = 0;
glo->save = 0;
glo->arg_checker = 0;
glo->sprite_num = 0;
glo->infos = NULL;
}

int ft_cub_parsing(t_mlx *glo, char *argv[])
{
int i;
int fd;
int ret;
int x;
char buffer[100];
char *temp;

x = 0;
i = 0;
fd = open(argv[1], O_RDONLY);
if (fd < 1)
{
    ft_putstr_fd("Error\nopen .cub error \n", 1);
    exit(1);
}
ret = read(fd, buffer, 10);
buffer[ret] = '\0';
glo->infos = ft_strdup(buffer);
while ((ret = read(fd, buffer, 10)))
{
buffer[ret] = '\0';
temp = ft_strdup(glo->infos);
free(glo->infos);
glo->infos = ft_strjoin(temp, buffer);
free(temp);
}
if (close(fd) == -1)
ft_error_msg("ERROR\ncant close file");
while (glo->infos[i])
{
if ((((glo->infos[i] > 32 && glo->infos[i] < 'A')) || ((glo->infos[i] > 'Z' && glo->infos[i] < 127))) && glo->infos[i] != ' ' && glo->infos[i] != '\t' && glo->infos[i] != '\v' && glo->infos[i] != '\f' && glo->infos[i] != '\r' && glo->infos[i] != '\n')
ft_error_msg("Error\nwrong info in .cub");
if (glo->infos[i] == 'R' && (glo->infos[i + 1] == ' ' || glo->infos[i + 1] == '\t' || glo->infos[i + 1] == '\v' || glo->infos[i + 1] == '\f' || glo->infos[i + 1] == '\r'))
i = ft_resolution(glo, i);
if (glo->infos[i] == 'N' && glo->infos[i + 1] == 'O' && (glo->infos[i + 2] == ' ' || glo->infos[i + 2] == '\t' || glo->infos[i + 2] == '\v' || glo->infos[i + 2] == '\f' || glo->infos[i + 2] == '\r'))
i = ft_path_texture(glo, i, glo->text_no);
if (glo->infos[i] == 'S' && glo->infos[i + 1] == 'O' && (glo->infos[i + 2] == ' ' || glo->infos[i + 2] == '\t' || glo->infos[i + 2] == '\v' || glo->infos[i + 2] == '\f' || glo->infos[i + 2] == '\r'))
i = ft_path_texture(glo, i, glo->text_so);
if (glo->infos[i] == 'W' && glo->infos[i + 1] == 'E' && (glo->infos[i + 2] == ' ' || glo->infos[i + 2] == '\t' || glo->infos[i + 2] == '\v' || glo->infos[i + 2] == '\f' || glo->infos[i + 2] == '\r'))
i = ft_path_texture(glo, i, glo->text_we);
if (glo->infos[i] == 'E' && glo->infos[i + 1] == 'A' && (glo->infos[i + 2] == ' ' || glo->infos[i + 2] == '\t' || glo->infos[i + 2] == '\v' || glo->infos[i + 2] == '\f' || glo->infos[i + 2] == '\r'))
i = ft_path_texture(glo, i, glo->text_ea);
if (glo->infos[i] == 'S' && (glo->infos[i + 1] == ' ' || glo->infos[i + 1] == '\t' || glo->infos[i + 1] == '\v' || glo->infos[i + 1] == '\f' || glo->infos[i + 1] == '\r'))
i = ft_path_texture(glo, i, glo->text_sprite);
if (glo->infos[i] == 'F' && (glo->infos[i + 1] == ' ' || glo->infos[i + 1] == '\t' || glo->infos[i + 1] == '\v' || glo->infos[i + 1] == '\f' || glo->infos[i + 1] == '\r'))
i = ft_path_texture(glo, i, glo->text_floor);
if (glo->infos[i] == 'C' && (glo->infos[i + 1] == ' ' || glo->infos[i + 1] == '\t' || glo->infos[i + 1] == '\v' || glo->infos[i + 1] == '\f' || glo->infos[i + 1] == '\r'))
i = ft_path_texture(glo, i, glo->text_ceiling);
if (glo->arg_checker == 8)
break;
i++;
}
if (glo->arg_checker == 8)
ft_cub_to_map(x, glo);
free(glo->infos);
return (0);
}

int ft_resolution(t_mlx* glo, int i)
{
int y;
char temp[10];
char *buf;

y = 0;
i++;
while (glo->infos[i] == ' ' || glo->infos[i] == '\t' || glo->infos[i] == '\v' || glo->infos[i] == '\f' || glo->infos[i] == '\r')
i++;
while (glo->infos[i] && (glo->infos[i] >= '0' && glo->infos[i] <= '9') && y < 10)
{
temp[y] = glo->infos[i];
y++;
i++;
}
temp[y] = '\0';
glo->resX = ft_atoi(temp);
temp[0] = '\0';
y = 0;
while (glo->infos[i] == ' ' || glo->infos[i] == '\t' || glo->infos[i] == '\v' || glo->infos[i] == '\f' || glo->infos[i] == '\r')
i++;
while (glo->infos[i] && (glo->infos[i] >= '0' && glo->infos[i] <= '9'))
{
temp[y] = glo->infos[i];
y++;
i++;
}
temp[y] = '\0';
glo->resY = ft_atoi(temp);
glo->arg_checker++;
buf = ft_substr(glo->infos, i, ft_strlen(glo->infos) - i);
free(glo->infos);
glo->infos = ft_strdup(buf);
free(buf);
return (0);	
}

int    ft_path_texture(t_mlx* glo, int i, char *texture)
{
int y;
char *buf;

y = 0;
i = i + 2;
while (glo->infos[i] == ' ' || glo->infos[i] == '\t' || glo->infos[i] == '\v' || glo->infos[i] == '\f' || glo->infos[i] == '\r')
i++;
while (glo->infos[i])
{
	if (glo->infos[i] == ' ' || glo->infos[i] == '\t' || glo->infos[i] == '\v' || glo->infos[i] == '\f' || glo->infos[i] == '\r' || glo->infos[i] == '\n')
	break;
texture[y] = glo->infos[i];
y++;
i++;
}
texture[y] = '\0';
ft_test_textures(texture);
glo->arg_checker++;
buf = ft_substr(glo->infos, i, ft_strlen(glo->infos) - i);
free(glo->infos);
glo->infos = ft_strdup(buf);
free(buf);
return (0);
}

int ft_cub_to_map(int i, t_mlx *glo)
{
	int x;

	x = 0;
	i = 0;
	/*printf("test\n");*/
	/*printf("info = %s\n", glo->infos);*/
	while (glo->infos[i] == '\n')
	{
		/*printf("test\n");*/
		i++;
	}	
	while (glo->infos[i])
	{
		glo->map_str[x] = glo->infos[i];
		x++;		
		i++;
	}
	glo->map_str[x] = '\0';
	return (0);
}