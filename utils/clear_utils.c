#include "../cub3D.h"

void    clear_setup(t_setup *setup)
{
    free(setup->player);
    free(setup->tables);
    free(setup->win);
    free(setup->image);
    // free_config(setup->map); //uncommented this somehow triggers segfault
    free(setup);
    // do we need to do something with mlx image?
}
