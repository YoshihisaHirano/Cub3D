#include "../cub3D.h"


void	draw_rectangle2(t_img *img, t_rectangle *params, int color)
{
	int i;
	int j;

	i = 0;
	while (i < params->height)
	{
		j = 0;
		while (j < params->width)
		{
			if (!i || i == params->height - 1 || !j || j == params->width - 1)
				my_pix_put(img, params->x + j, params->y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_setup *setup, t_img *img, t_rectangle *rec)
{

	rec->x = (setup->player->x) / PLAYER_SPEED * (rec->width / 4);
	rec->y = (setup->player->y) / PLAYER_SPEED * (rec->height / 4);
	printf("x %d\n", rec->x);
	rec->height = 5;
	rec->width = 5;
	draw_rectangle(img, rec, create_trgb(100, 255, 100, 0));
}

void draw_map_pixel(t_setup *setup, t_img *img, t_rectangle *rec, int x, int y)
{
	rec->x = x * rec->width;
	rec->y = y * rec->height;
	if ((setup->map->map)[y][x] == ' ')
		draw_rectangle(img, rec, create_trgb(50, 50, 150, 50));
	else if ((setup->map->map)[y][x] == '1')
		draw_rectangle(img, rec, create_trgb(50, 153, 0, 0));
	else if ((setup->map->map)[y][x] != '\0')
		draw_rectangle(img, rec, create_trgb(50, 0, 0, 102));
	else if ((setup->map->map)[y][x] == '\0')
		draw_rectangle(img, rec, create_trgb(50, 0, 0, 255));
	draw_rectangle2(img, rec, create_trgb(50, 0, 0, 0));
	
}

void    draw_minimap(t_setup *setup)
{
	t_rectangle rec;
	t_img   img;
	int x;
	int y;

	rec.width = (MINI_MAP_WIDTH - MINI_MAP_WIDTH % setup->map->max_line) / (setup->map->max_line);
	rec.height = (MINI_MAP_HEIGHT - MINI_MAP_HEIGHT % setup->map->map_size) / setup->map->map_size;
	img.img = mlx_new_image(setup->win->mlx_ptr,
		MINI_MAP_WIDTH - MINI_MAP_WIDTH % (setup->map->max_line),
		MINI_MAP_HEIGHT - MINI_MAP_HEIGHT % setup->map->map_size);
	img.addr = mlx_get_data_addr(img.img, &(img.bpp),
			&(img.line_len), &(img.endian));	
	y = 0;
	while (y < setup->map->map_size)
	{
		x = 0;
		while (x < setup->map->max_line)
			draw_map_pixel(setup, &img, &rec, x++, y);
		y++;
	}
	draw_player(setup, &img, &rec);
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr,
			img.img, 15, 15);
}