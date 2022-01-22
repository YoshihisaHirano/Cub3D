#include "../cub3D.h"

int     get_color_from_tex(t_setup *setup, int x, int y)
{
    int         color;
    t_texture   tex;

    tex = setup->texture[setup->col->wall_dir];
    color = tex.texture[y * tex.width + x];
    return (color);
}

void    assign_wall_dir(t_column *col, int curr_angle)
{
    col->ray_up = !facing_down(curr_angle);
    col->ray_left = !facing_right(curr_angle);
    if (!col->ray_up && !col->vertical_hit)
        col->wall_dir = NORTH;
    if (col->ray_up && !col->vertical_hit)
        col->wall_dir = SOUTH;
    if (col->ray_left && col->vertical_hit)
        col->wall_dir = EAST;
    if (!col->ray_left && col->vertical_hit)
        col->wall_dir = WEST;
    // printf("%d - curr_angle, %d - column_no, %d ray_up, %d ray_left, %d wall_dir, %d - v_hit\n", curr_angle, col->no, col->ray_up, col->ray_left, col->wall_dir, col->vertical_hit);
}

t_point find_start_pixel(t_setup *setup)
{
    t_point pixel_pos;

    pixel_pos.x = fmod(setup->col->h_intersec.x, TILE_SIDE)
        / TILE_SIDE * setup->texture[setup->col->wall_dir].width;
    if (setup->col->vertical_hit)
    {
        pixel_pos.x = fmod(setup->col->v_intersec.y, TILE_SIDE)
            / TILE_SIDE * setup->texture[setup->col->wall_dir].width;
    }
    pixel_pos.y = 0;
    return (pixel_pos);
}



void    render_tex_column(t_setup *setup, int wall_top, int wall_bottom)
{
    t_point curr_pix;
    double  y_step;
    int     y;
    int     wall_height;
    int     color;

    curr_pix = find_start_pixel(setup);
    wall_height = (wall_bottom - wall_top + 1); 
    y_step = 1.0 * setup->texture[setup->col->wall_dir].height / wall_height;
    y = curr_pix.y;
    while (y < wall_height)
    {
        color = get_color_from_tex(setup, (int)curr_pix.x, (int)curr_pix.y);
        my_pix_put(setup->image, setup->col->no, wall_top + y, color);
        curr_pix.y = curr_pix.y + y_step;
        y++;
    }
}