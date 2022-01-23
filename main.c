#include "cub3D.h"

int main(int argc, char **argv)
{
	t_setup		*setup;
	t_map 		*map;

    if (argc < 2)
		return (1);
	map = parser(argv[1]);
    if (map == NULL)
    {
        printf("------parser error\n");
        return (0);
    }
	setup = init_all();
	setup->map = map;
	load_textures(setup);
	// DDA
	setup->player->pos->x = 5.5;
	setup->player->pos->y = 5.5;
	setup->player->dir->x = 0.0;
	setup->player->dir->y = -1.0;
	setup->plane->x = -FOV;
	setup->plane->y = 0.0;
	//
	mlx_key_hook(setup->win->win_ptr, key_hook, setup);
	draw_plane(setup);
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
	mlx_loop(setup->win->mlx_ptr);
	free_config(map);
	return (0);
}



// TODO change name for map_size line_size
// TODO check if around player spaces
//				 s
//			    s0s
//				 s


