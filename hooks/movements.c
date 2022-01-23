#include "hooks.h"

bool	allow_movement_x(t_setup *setup, double delta_x)
{
	if ((setup->player->pos->x + delta_x) < 1
		|| (setup->player->pos->x + delta_x) >= setup->map->max_line)
		return (false);
	if (check_wall(setup->map, (int)(setup->player->pos->x + delta_x),
		(int)(setup->player->pos->y)))
		return (false);
	return (true);
}

bool	allow_movement_y(t_setup *setup, double delta_y)
{
	if ((setup->player->pos->y + delta_y) < 1
		|| (setup->player->pos->y + delta_y) >= setup->map->map_size)
		return (false);
	if (check_wall(setup->map, (int)(setup->player->pos->x),
		(int)(setup->player->pos->y + delta_y)))
		return (false);
	return (true);
}

void	dda_move_forward_backward(t_setup *setup, bool forward)
{
	t_player	*p;
	double		delta_x;
	double		delta_y;

	p = setup->player;
	delta_x = p->dir->x * PLAYER_SPEED;
	delta_y = p->dir->y * PLAYER_SPEED;
	if (!forward)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (allow_movement_y(setup, delta_y) && allow_movement_x(setup, delta_x))
	{
		setup->player->pos->y += delta_y;
		setup->player->pos->x += delta_x;
	}
	draw_plane(setup);
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr,
		setup->image->img, 0, 0);
	draw_minimap(setup);
}

void	dda_move_left_right(t_setup *setup, bool left)
{
	t_player	*p;
	double		delta_x;
	double		delta_y;

	p = setup->player;
	delta_x = setup->plane->x * PLAYER_SPEED;
	delta_y = setup->plane->y * PLAYER_SPEED;
	if (left)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (allow_movement_y(setup, delta_y) && allow_movement_x(setup, delta_x))
	{
		setup->player->pos->y += delta_y;
		setup->player->pos->x += delta_x;
	}
	draw_plane(setup);
	mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr,
		setup->image->img, 0, 0);
	draw_minimap(setup);
}
