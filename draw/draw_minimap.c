#include "../cub3D.h"


void draw_map_pixel(t_setup *setup, t_img *img, t_rectangle *rec, int x, int y)
{
	rec->x = x;
	rec->y = y;
	(void) setup;
	if ((setup->map->map)[y / rec->height][x / rec->width] == ' ')
		draw_rectangle(img, rec, create_trgb(50, 0, 0, 100));
	if ((setup->map->map)[y / rec->height][x / rec->width] == '1')
		draw_rectangle(img, rec, create_trgb(50, 0, 100, 100));
	else
		draw_rectangle(img, rec, create_trgb(50, 100, 100, 0));
}

void    draw_minimap(t_setup *setup)
{
	t_rectangle rec;
	t_img   img;
	int x;
	int y;

	rec.width = MINI_MAP_WIDTH / setup->map->max_line;
	rec.height = MINI_MAP_HEIGHT / setup->map->map_size + 1;
	img.img = mlx_new_image(setup->win->mlx_ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &(img.bpp),
								  &(img.line_len), &(img.endian));
								
	y = 0;    

	while (y < MINI_MAP_HEIGHT)
	{
		x = 0;
		while (x < MINI_MAP_WIDTH)
		{
			draw_map_pixel(setup, &img, &rec, x, y);
			x += rec.width;
		}
		y += rec.height;
	}
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr,
			img.img, 15, 15);
}