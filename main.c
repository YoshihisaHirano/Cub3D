#include "cub3D.h"

char **create_map();
void    print_map(char **map);
void    draw_plane(t_ppov *p, char **map, t_img *img);

void    init_win(t_win *win)
{
    win->mlx_ptr = mlx_init();
    win->height = HEIGHT;
    win->width = WIDTH;
    win->win_ptr = mlx_new_window(win->mlx_ptr,
			win->width, win->height, "Cub3D");
}

void    init_img(t_img *img, t_win *win)
{
    img->img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line_len), &(img->endian));
}

int    exit_prog(t_win *win)
{
    (void)win;
    exit(0);
    return (0);
}

int main()
{
    t_win win;
    t_img img;
    t_ppov  p;

    init_win(&win);
    init_img(&img, &win);
    mlx_key_hook(win.win_ptr, key_hook, NULL);
    // mlx_hook(win.mlx_ptr, EV_DESTR_NOTIFY, MASK_NO_EVENT, exit_prog, &win); check why this doesn't work
    char ** map = create_map(); // think of map representation, probably linked lists
    // print_map(map);
    // these values will be extracted from map and will change with regards to key/mouse events:
    p.player_x = 96;
    p.player_y = 224;
    p.player_angle = 45;
    draw_plane(&p, map, &img);
    mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.img, 0, 0);
    mlx_loop(win.mlx_ptr);
}
