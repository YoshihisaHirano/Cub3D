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
}

void    move_forwards_backwards(t_setup *setup, bool forwards)
{
    double  x_dir;
    double  y_dir;

    x_dir = setup->tables->cos[setup->player->angle];
    y_dir = setup->tables->sin[setup->player->angle];
    if (forwards)
    {
        setup->player->x += (int)(x_dir * PLAYER_SPEED);
        setup->player->y += (int)(y_dir * PLAYER_SPEED);
    }
    else
    {
        setup->player->x -= (int)(x_dir * PLAYER_SPEED);
        setup->player->y -= (int)(y_dir * PLAYER_SPEED);
    }
    printf("%d - x, %d - y\n", setup->player->x, setup->player->y);
    draw_plane(setup);
    mlx_put_image_to_window(setup->win->mlx_ptr, setup->win->win_ptr, setup->image->img, 0, 0);
}

void    move_left_right(t_setup *setup, bool left)
{
    (void)setup;
    (void)left;
}
