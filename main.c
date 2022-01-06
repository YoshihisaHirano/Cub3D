#include "cub3D.h"

int main(int argc, char **argv)
{
	t_config	*config;
	t_map 		*map;
	t_win		win;
	t_img		img;

    if (argc < 2)
		return (1);
	map = parser(argv[1]);
    if (map == NULL)
    {
        printf("parser error\n");
        return (0);
    }
	init_win(&win);
	init_img(&img, &win);
	config = create_main_config();
	config->image = &img;
	draw_plane(config);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, config->image->img, 0, 0);
	mlx_loop(win.mlx_ptr);
	return (0);
}





