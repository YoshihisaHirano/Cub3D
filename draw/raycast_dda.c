#include "../cub3D.h"

void    find_wall_dir(t_column *col, t_setup *setup)
{
    if (col->vertical_hit)
    {
        if (setup->player->dir->y < 0)
            col->wall_dir = NORTH;
        else
            col->wall_dir = SOUTH;
    }
    else
    {
        if (setup->player->dir->x < 0)
            col->wall_dir = WEST;
        else
            col->wall_dir = EAST;
    }
}

int     get_color(t_setup *setup, int x, int y)
{
    int         color;
    t_texture   tex;

    tex = setup->texture[setup->col->wall_dir];
    color = tex.texture[y * tex.width + x];
    return (color);
}

void    render(t_setup *setup)
{
    double  cameraX;
    t_point deltas;
    t_point step;
    t_point ray_dir;
    t_point on_map;
    t_point side_dist;

    cameraX = 2 * setup->col->no / (double)PLANE_WIDTH - 1;
    // printf("%lf - cameraX, %d - col\n", cameraX, setup->col->no);
    ray_dir.x = setup->player->dir->x + setup->plane->x * cameraX;
    ray_dir.y = setup->player->dir->y + setup->plane->y * cameraX;
    // printf("%lf - dirX, %lf - dirY\n", ray_dir.x, ray_dir.y);
    on_map.x = floor(setup->player->pos->x);
    on_map.y = floor(setup->player->pos->y);

    // fabs(1. / obj->dir.x), fabs(1. / obj->dir.y)
    deltas.x = fabs(1.0 / ray_dir.x);
    deltas.y = fabs(1.0 / ray_dir.y);

    step = (t_point){ .x = 1, .y = 1 };
    side_dist.x = (on_map.x + 1.0 - setup->player->pos->x) * deltas.x;
    side_dist.y = (on_map.y + 1.0 - setup->player->pos->y) * deltas.y;
    if (ray_dir.x < 0)
    {
        step.x = -1;
        side_dist.x = (setup->player->pos->x - on_map.x) * deltas.x;
    }
    if (ray_dir.y < 0)
    {
        step.y = -1;
        side_dist.y = (setup->player->pos->y - on_map.y) * deltas.y;
    }
    // loop until the wall is hit
    int hit;
    hit = 0;
    while (hit == 0)
    {
        if (side_dist.x < side_dist.y)
        {
            side_dist.x += deltas.x;
            on_map.x += step.x;
            setup->col->vertical_hit = 0;
        }
        else
        {
            side_dist.y += deltas.y;
            on_map.y += step.y;
            setup->col->vertical_hit = 1;
        }
        hit = check_wall(setup->map, (int)on_map.x, (int)on_map.y);
    }

    // find wall height, top and bottom
    int     wall_height;
    double  wall_dist;
    int     wall_top;
    int     wall_bottom;

    // if (side == 0)
	// 		perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
	// 		else
	// 		perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
    wall_dist = fabs((on_map.y - setup->player->pos->y + (1.0 - step.y) / 2.0) / ray_dir.y);
    if (setup->col->vertical_hit == 0)
        wall_dist = fabs((on_map.x - setup->player->pos->x + (1.0 - step.x) / 2.0) / ray_dir.x);
    wall_height = abs((int)(PLANE_HEIGHT / wall_dist));
    // printf("%lf - wall_dist\n", wall_dist);
    wall_top = -wall_height / 2 + PLANE_HEIGHT / 2;
    if (wall_top < 0)
        wall_top = 0;
    wall_bottom = wall_height / 2 + PLANE_HEIGHT / 2;
    if (wall_bottom >= PLANE_HEIGHT)
        wall_bottom = PLANE_HEIGHT - 1;
    wall_height = wall_bottom - wall_top + 1;

    find_wall_dir(setup->col, setup);

    // find x coordinate of the texture
    double  wall_hit_x;
    int     texture_x;

    wall_hit_x = setup->player->pos->x + wall_dist * ray_dir.x;
    if (setup->col->vertical_hit == 0)
    wall_hit_x = setup->player->pos->y + wall_dist * ray_dir.y;
    wall_hit_x -= floor(wall_hit_x);
    texture_x = (int)(wall_hit_x * setup->texture[setup->col->wall_dir].width);
    if ((setup->col->vertical_hit == 0 && ray_dir.x > 0)
        || (setup->col->vertical_hit == 1 && ray_dir.y < 0))
        texture_x = setup->texture[setup->col->wall_dir].width - texture_x - 1;
    
    //drawing with texture
    t_point curr_pix;
    int     y;
    double  y_step;
    int     color;

    curr_pix.x = texture_x;
    // printf("%lf - curr_pix.x\n", curr_pix.x);
    curr_pix.y = 0;
    y_step = 1.0 * setup->texture[setup->col->wall_dir].height / (double)wall_height;
    // printf("%d - wall_top, %d - wall_bottom, %lf - y_step\n", wall_top, wall_bottom, y_step);
    y = curr_pix.y;
    while (y < wall_height)
    {
        color = get_color(setup, (int)curr_pix.x, (int)curr_pix.y);
        my_pix_put(setup->image, setup->col->no, wall_top + y, color);
        curr_pix.y = curr_pix.y + y_step;
        y++;
    }
}