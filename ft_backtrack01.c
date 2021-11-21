#include "header.h"

/* mettre filleur avant le check de mur ,commencer apd la pos du joueur pour fill et check que le mur soit tjs pres du sol*/
int ft_backtrack_filler(int x, int y, t_mlx *glo)
{
    if (x >= 0 && y >= 0 && x < glo->maxX && y < glo->maxY && glo->soluce[x][y] == 0 && glo->themap[x][y] == 0)
    {
        glo->soluce[x][y] = 2;
        if (y + 1 < glo->maxY)
        {
        if (ft_backtrack_filler(x, y + 1, glo))
            return 1;
        }
        if (x + 1 < glo->maxX)
        {
        if (ft_backtrack_filler(x + 1, y, glo))
            return 1;
        }
        if (x - 1 > 0)
        {
        if (ft_backtrack_filler(x - 1, y, glo))
            return 1;
        }
        if (y - 1 > 0)
        {
        if (ft_backtrack_filler(x, y - 1, glo))
            return 1;
        }
    }
    return 0;
}

int ft_find_map_hole(t_mlx *glo)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < glo->maxX && y <= glo->maxY)
    {
        if (glo->soluce[x][y] == 2)
        {
        if (glo->themap[x][y] == 3)
        ft_error_msg("map isn't complete or hole in walls");
        if (glo->themap[x + 1][y] == 3)
        ft_error_msg("map isn't complete or hole in walls");
        if (glo->themap[x][y + 1] == 3)
        ft_error_msg("map isn't complete or hole in walls");
        if (glo->themap[x - 1][y] == 3)
        ft_error_msg("map isn't complete or hole in walls");
        if (glo->themap[x][y - 1] == 3)
        ft_error_msg("map isn't complete or hole in walls");
        }
        //voir si la map soluce et themap leak
        //si 3 proche de 2 = leak
        x++;
        if (x == glo->maxX)
        {
            y++;
            x = 0;
        }
    }
    return (1); 
}