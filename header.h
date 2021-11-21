/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:49:16 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:36:13 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

/* POUR COMPILER SUR LINUX, UTILISER CES FLAGS ==.
gcc "test.c" -lmlx -lXext -lX11 -L minilibx-linux-master/libmlx.a ou minilibx-linux-master/libmlx_Linux.a
gcc main.c -lmlx -lXext -lX11 -L minilibx-linux-master/libmlx_Linux.a /home/ldavids/19-master/cube_3d/Libft/libft.a
    POUR MACOS, utiliser cela = 
    gcc -I /usr/local/include -g -L /usr/local/lib -l mlx -framework OpenGL -framework AppKit main.c raycast.c t
extures.c ft_backtrack01.c hook.c bmp.c ft_parsing.c convert.c cub_to_struct.c /Users/ldavids/Laurent/cube_3d_07.10.2020/Libft/lib
ft.a*/

#include "Libft/libft.h"

#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>

typedef struct s_sprites
{
double x;
double y;
} t_sprites;

typedef struct s_textures
{
    void *img_ptr;
    char *data;
    int size_l;
    int bpp;
    int endian;
} t_textures;

typedef struct s_mlx
{
    t_textures textures[10];  //10 textures max
    t_sprites sprites [20];     //20 sprites max
    int **themap;                   //contains the 1 and 0 to parse the map
    void *mlx_ptr;                 //pointer on minilbx
    void *win;                      //the window created
    void *img;                          //the img data that will be displayed 
    void *img_data;                     //  contains all pixels and stuff - associate img with img_data through mlx_get_data_addr
    unsigned int  color_hex;            
    int size_l;                         //used for img_data
    int bpp;                               //used for img_data
    int endian;                                 //used for img_data
    
    /* raycast variables */
    double posX;
    double posY;
    double ray_posX;
    double ray_posY;
    double dirX;
    double dirY;
    double old_dirX;
    double planeX;
    double planeY;
    double old_planeX;
    double cameraX;
    double rayDirX;
    double rayDirY;
    double latspeed;
    double speed;
    int x;
    int y;
    int time;
    int oldtime;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    int lineHeight;
    int drawstart;
    int drawend; 
    int color;
    char *color2;
    int text_num;
    double wallX;
    int texX;
    int texY;
    float raydirX0;
    float raydirX1;
    float raydirY0;
    float raydirY1;
    float posZ;
    float rowdistance;
    float floorstepX;
    float floorstepY;
    float floorX;
    float floorY;
    int cellX;
    int cellY;
    int tx;
    int ty;
    int floortexture;
    int ceilingtexture;
    /* hook variables */
    int escape;
    int up;
    int down;
    int left;
    int right;
    int move_mouseX;
    int move_mouseY;
    int strafe_l;
    int strafe_r;
    /* sprites */
    double *zbuffer;
    int sprite_num;
    int sprite_order[50];
    double sprite_distance[50];
    double spriteX;
    double spriteY;
    double invDet;
    double transformX;
    double transformY;
    int spriteScreenX;
    int spriteHeight;
    int spriteWidth;
    /* raycast and stuff */
    int drawstartY;
    int drawendY;
    int drawstartX;
    int drawendX;
    int stripe;
    int ceiling_on;
    int save;
    int resX;       //X resolution
    int resY;       //Y resolution
    char text_no[50];
    char text_so[50];
    char text_we[50];
    char text_ea[50];
    char text_floor[50];
    char text_ceiling[50];
    char text_sprite[50];
    int arg_checker;
    char map_str[8000];
    int maxX;
    int maxY;
    int posInitX;
    int posInitY;
    char player_ori;
    char *infos;
    int **soluce;
    int player_x;
    int player_y;
    int player_numb;
} t_mlx;

struct rgb_data {
float r;
float g;
float b;
};

struct bitmap_file_header {
    unsigned char   bitmap_type[2];     // 2 bytes
    int             file_size;          // 4 bytes
    short           reserved1;          // 2 bytes
    short           reserved2;          // 2 bytes
    unsigned int    offset_bits;        // 4 bytes
} bfh;

struct bitmap_image_header {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
} bih;

typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
} pixel;

int ft_backtrack_filler(int x, int y, t_mlx *glo);
int ft_find_map_hole(t_mlx *glo);
int ft_str_to_array(t_mlx *glo);
void ft_count(char *str, t_mlx *glo);
int key_press(int keycode, t_mlx *glo);
int key_release(int keycode, t_mlx *glo);
int button_press(int button, int x, int y, t_mlx *glo);
int ft_move(t_mlx *glo);
void ft_move_side(t_mlx *glo);
int ft_exit(void);
int ft_screen_init(t_mlx *glo);
void ft_raycast_init(t_mlx *glo, int x);
void ft_raycast(t_mlx *glo);
void ft_dda_init(t_mlx *glo);
void ft_dda(t_mlx *glo);
void    ft_reset(t_mlx *glo);
void ft_draw_floor_ceiling(t_mlx *glo, int x);
void ft_floor_ceiling_text(t_mlx *glo, int x);
void ft_draw_walls(int x, int start, int end, t_mlx *glo);
void ft_print_map(t_mlx *glo);
void ft_pixel_into_img(t_mlx *glo, int x, int y, int color);
void textures_init(t_mlx *glo);
void    ft_orientation_init(t_mlx *glo);
void ft_sprites(t_mlx *glo);
void ft_sort_basic(t_mlx *glo);
void ft_sprite_draw(t_mlx *glo);
void ft_sky(t_mlx *glo);
int mouse_capture(int x, int y, t_mlx *glo);
void ft_move_mouse(t_mlx *glo);
void save_bitmap(char*file, int dpi, t_mlx *glo);
int writeBMP(char* filename, unsigned int width, unsigned int height, pixel** pixels);
void bmp_generator(t_mlx *glo);
void ft_int_to_hex(unsigned long n, char *outbuf);
int two_hex_to_int(char *temp);
int ft_color_div(int x);
void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);
int ft_cub_parsing(t_mlx *glo, char *argv[]);
int ft_check_argc_v(int argc, char *argv[], t_mlx *glo);
int    ft_resolution(t_mlx* glo, int i);
int    ft_path_texture(t_mlx* glo, int i, char* no);
void    struct_init(t_mlx *glo);
int ft_cub_to_map(int i, t_mlx *glo);
int ft_parsing(t_mlx *glo);
void ft_error_check(int x, t_mlx *glo);
void ft_error_msg(char *str);
void ft_free(t_mlx *glo);
void ft_test_textures(char *str);

#endif