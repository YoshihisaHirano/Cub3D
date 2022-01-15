#include "../cub3D.h"

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
}

t_point find_start_pixel(t_setup *setup)
{
    t_point pixel_pos;

    pixel_pos.x = (int)fmod(setup->col->h_intersec.x, TILE_SIDE)
        / TILE_SIDE * setup->texture[setup->col->wall_dir].width;
    if (setup->col->vertical_hit)
    {
        pixel_pos.x = (int)fmod(setup->col->v_intersec.y, TILE_SIDE)
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
        // color = get_color - from texture;
        // my_pix_put(setup->img, curr_pix.x, y, color);
        y = (int)floor(y + y_step);
    }
}