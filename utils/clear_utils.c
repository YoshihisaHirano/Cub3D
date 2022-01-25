#include "../cub3D.h"

void    clear_setup(t_setup *setup)
{
    int i;

    i = 0;
    // free(setup->player->pos);
    // free(setup->player->dir);
    // free(setup->player);
    free(setup->tables);
    free(setup->plane);
    free(setup->win);
    free(setup->image);
    while (i < 4)
    {
        free(setup->texture[i].texture);
        i++;
    }
    free(setup);
    // do we need to do something with mlx image?
}
