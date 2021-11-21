#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

static int	ft_len(long int n)
{
	int				i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char		*ft_itoa(int n)
{
	long int		i;
	char			*str;
	long int		negatif;
	long int		nb;

	negatif = 0;
	nb = (long int)n;
	if (nb < 0)
	{
		negatif = 1;
		nb = -nb;
	}
	i = ft_len(nb) + negatif;
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = nb % 10 + 48;
		nb = nb / 10;
	}
	if (negatif == 1)
		str[0] = '-';
	return (str);
}

# define WIN_WIDTH 50
# define WIN_HEIGHT 50

typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_stru
{
	void		*mlx_ptr;
	void		*win;
    int         escape;
	t_img		img;
}				t_stru;

int key_press(int keycode, t_stru *glo)
{
    if (keycode != 0)
    {
    if (keycode == 65307)
    glo->escape++;
    char* reveal = NULL;
    reveal = ft_itoa(keycode);
    mlx_clear_window(glo->mlx_ptr, glo->win);
    mlx_string_put (glo->mlx_ptr, glo->win, 10, 25, 0xEEEEEE, reveal);
    if (glo->escape >= 3 && keycode == 65307)
    exit(1);
    }
}

int	main(void)
{
	t_stru	glo; 

    glo.escape = 0;
	glo.mlx_ptr = mlx_init();
	glo.win = mlx_new_window(glo.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Keycode Machine");
	glo.img.img_ptr = mlx_new_image(glo.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	glo.img.data = (int *)mlx_get_data_addr(glo.img.img_ptr, &glo.img.bpp, &glo.img.size_l,
		&glo.img.endian);
	mlx_put_image_to_window(glo.mlx_ptr, glo.win, glo.img.img_ptr, 0, 0);
    mlx_key_hook (glo.win, key_press, &glo);
	mlx_loop(glo.mlx_ptr);
	return (0);
}