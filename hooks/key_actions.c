#include "hooks.h"

void    turn(t_setup *setup, bool left)
{
    if (left)
    {
        setup->player->angle -= ANGLE10;
        if (setup->player->angle < ANGLE0)
            setup->player->angle += ANGLE360;
    }
    else
    {
        setup->player->angle += ANGLE10;
        if (setup->player->angle > ANGLE360)
            setup->player->angle -= ANGLE360;
    }
    draw_plane(setup);
    mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
	draw_minimap(setup);
}

bool	out_of_map(t_setup *setup, int x_increment, int y_increment, bool forwards)
{
	t_player	*player;
	int			map_width;
	int			map_height;

	player = setup->player;
	map_width = setup->map->max_line * TILE_SIDE;
	map_height = setup->map->map_size * TILE_SIDE;
	if (forwards)
		return ((player->x + x_increment > map_width)
			|| (player->y + y_increment > map_height));
	return ((player->x - x_increment < 0)
			|| (player->y - y_increment < 0));
}

void    move_forwards_backwards(t_setup *setup, bool forwards)
{
    double  x_dir;
    double  y_dir;

    x_dir = setup->tables->cos[setup->player->angle];
    y_dir = setup->tables->sin[setup->player->angle];
	if (out_of_map(setup, floor(x_dir * PLAYER_SPEED), floor(y_dir *
	PLAYER_SPEED), forwards))
		return;
    if (forwards)
    {
        setup->player->x += floor(x_dir * PLAYER_SPEED);
        setup->player->y += floor(y_dir * PLAYER_SPEED);
    }
    else
    {
        setup->player->x -= floor(x_dir * PLAYER_SPEED);
        setup->player->y -= floor(y_dir * PLAYER_SPEED);
    }
    draw_plane(setup);
    mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
	draw_minimap(setup);
}

void    move_left_right(t_setup *setup, bool left)
{
    double  x_dir;
    double  y_dir;

    y_dir = setup->tables->cos[setup->player->angle];
    x_dir = setup->tables->sin[setup->player->angle];
	if (out_of_map(setup, floor(x_dir * PLAYER_SPEED), floor(y_dir *
	PLAYER_SPEED), left))
		return;
    if (left)
    {
        setup->player->x += floor(x_dir * PLAYER_SPEED);
        setup->player->y -= floor(y_dir * PLAYER_SPEED);
    }
    else
    {
        setup->player->x -= floor(x_dir * PLAYER_SPEED);
        setup->player->y += floor(y_dir * PLAYER_SPEED);
    }
    draw_plane(setup);
    mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
	draw_minimap(setup);
}
