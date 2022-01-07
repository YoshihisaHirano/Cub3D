#include "../cub3D.h"

void	exit_procedure(t_setup *setup)
{
    clear_setup(setup);
    exit(0);
}

void    turn(t_setup *setup, bool left)
{
    if (left)
        setup->player->angle -= ANGLE10;
    else
        setup->player->angle += ANGLE10;
    if (setup->player->angle < ANGLE0)
        setup->player->angle += ANGLE360;
    if (setup->player->angle > ANGLE360)
        setup->player->angle -= ANGLE360;
    draw_plane(setup);
    mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
}

int key_hook(int key_code, t_setup *setup)
{
    if (key_code == KEYCODE_ESC)
        exit_procedure(setup);
    if (key_code == KEYCODE_LEFT)
        turn(setup, true);
    if (key_code == KEYCODE_RIGHT)
        turn(setup, false);
    return (0);
}