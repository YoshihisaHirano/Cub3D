#include "cub3D.h"

int main()
{
	t_config	*config;
	t_win		win;
	t_img		img;

	init_win(&win);
	init_img(&img, &win);
	config = create_config();
	config->image = &img;
	draw_plane(config);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, config->image->img, 0, 0);
	mlx_loop(win.mlx_ptr);
	return (0);
}