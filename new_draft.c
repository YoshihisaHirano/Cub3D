#include "cub3D.h"

double find_dst(t_config *config, int angle, int column)
{
	double	h_dst;
	double	v_dst;

	h_dst = dst_to_horizontal(config->tables, config->player, config->map, angle);
	v_dst = dst_to_vertical(config->tables, config->player, config->map, angle);
//	printf("%d - column\n", column);
//	printf("%lf - table data\n", config->tables->fish_table[column]);
	if (v_dst < h_dst)
		return (v_dst / config->tables->fish_table[column]);
	return (h_dst / config->tables->fish_table[column]);
}

int	wall_height(double dist)
{
//	printf("%d - wall height\n", (int)(TILE_SIDE * PLAYER_PLANE_DST / dist));
	return ((int)(TILE_SIDE * PLAYER_PLANE_DST / dist));
}

void	find_draw_column(t_config *config, int curr_angle, int column)
{
	double		dist;
	int			wall_top;
	int			wall_bottom;
	t_rectangle	rect;
	int			color;

	dist = find_dst(config, curr_angle, column);
	wall_top = (int)(PLANE_CENTER - (wall_height(dist) / 2));
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = (int)(PLANE_CENTER + (wall_height(dist) / 2));
	if (wall_bottom > PLANE_HEIGHT)
		wall_bottom = PLANE_HEIGHT - 1;
	rect.x = column;
	rect.y = wall_top;
	rect.height = (wall_bottom - wall_top + 1);
	rect.width = 2;
//	printf("%d - x, %d - y, %d - height, %d - width\n", rect.x, rect.y, rect
//	.height, rect.width);
	color = create_trgb(0, 150, 75, 0); // arbitrary color for now
	draw_rectangle(config->image, &rect, color);
}

void	draw_plane(t_config *conf)
{
	int		column;
	int		curr_angle;
//	int		ceil_color; //temp val
//	int		floor_color; // temp as well

	column = 0;
	curr_angle = conf->player->angle - ANGLE30;
	if (curr_angle < 0)
		curr_angle += ANGLE360;
//	ceil_color = create_trgb(0, 182, 213, 240); // arbitrary color for now
//	floor_color = create_trgb(0, 7, 129, 54); // arbitrary color for now

	while (column < PLANE_WIDTH)
	{
		find_draw_column(conf, curr_angle, column);
		column += 2;
		curr_angle += 2;
		if (curr_angle > ANGLE360)
			curr_angle -= ANGLE360;
	}
}

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