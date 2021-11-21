/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:58:07 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:45:53 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

const int BYTES_PER_PIXEL = 3; /// R,G,B
const int FILE_HEADER_SIZE = 14;    ///size of first header, always 14
const int INFO_HEADER_SIZE = 40;    ///size of second header, min 40   

int ft_color_div(int x) /// divide the RGB in hex with only R or G or B
{
char *temp;
int z;

z = x;
if (z > 0 && z < 16777215) //to limit from black to white - but shoud work anyway
{
temp = ft_itoa(x);
ft_int_to_hex(x, temp);
x = two_hex_to_int(temp);  //used to transform an hex 00006d in 6d then int or 6d00 in 6d then int
}
if (z > 0 && z < 16777215)
free(temp);
return (x);
}

void bmp_generator(t_mlx *glo)
{
    int height = glo->resY;
    int width = glo->resX;
    unsigned char image[height][width][BYTES_PER_PIXEL];
    char* imageFileName = (char*) "bitmapImage.bmp";
    char *mlx_data_addr;

    int y, x;
    y = 0;
    while (++y < glo->resY) 
    {
        x = 0;
        while (++x < glo->resX)
         {
            mlx_data_addr = glo->img_data + (y * glo->size_l + x * (glo->bpp / 8));
            glo->color_hex = *(unsigned int *)mlx_data_addr;
            
            image[glo->resY - y][x][2] = (unsigned char) (ft_color_div(glo->color_hex & (0xFF << 16)));            ///red
            image[glo->resY - y][x][1] = (unsigned char) (ft_color_div(glo->color_hex & (0xFF << 8))); ///green
            image[glo->resY - y][x][0] = (unsigned char) (ft_color_div(glo->color_hex & (0xFF)));   ///blue
        }
    }
    generateBitmapImage((unsigned char*) image, height, width, imageFileName);
    ft_putendl_fd("Image generated", 1);
}


void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
{
    int fd;
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    fd = open("saved_image.bmp", O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);   ///O_CREAT + S_IRUSR | S_IWUSR to create file (with permissions) incase it doesnt exist
    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    write(fd, fileHeader, FILE_HEADER_SIZE);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    write(fd, infoHeader, INFO_HEADER_SIZE);

    int i;
    for (i = 0; i < height; i++) 
    {
        write(fd, (image + (i*widthInBytes)), BYTES_PER_PIXEL * width);
        write(fd, padding, (paddingSize));     
    }
    close(fd);
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return infoHeader;
}