#include "../cub3D.h"

void    clear_setup(t_setup *setup)
{
    int i;

    i = 0;
	free_config(setup->map);
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
