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
        printf("parser error\n");
        return (0);
    }
	setup = init_all();
	mlx_key_hook(setup->win->win_ptr, key_hook, setup);
	draw_plane(setup);
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
	mlx_loop(setup->win->mlx_ptr);
	return (0);
}
