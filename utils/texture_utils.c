#include "../cub3D.h"

void    load_image(t_setup *s, char *path, t_img *img, int i)
{
    int *res;
    int j;

    img->img = mlx_xpm_file_to_image(s->win->mlx_ptr, path, &img->w, &img->h);
    if (!img->img)
        error_exit(TEXTURE_ERR);
    s->texture[i].width = img->w;
    s->texture[i].height= img->h;
    s->texture[i].texture = malloc(sizeof(int) * (img->w * img->h));
    img->addr = mlx_get_data_addr(img->img, &(img->bpp),
		&(img->line_len), &(img->endian));
    res = (int *)img->addr;
    j = 0;
    while (j < (img->w * img->h))
    {
        s->texture[i].texture[j] = res[j];
        j++;
    }
    // printf("%d - first int\n", s->texture[i].texture[0]);
    // mlx_destroy_image(s->win->mlx_ptr, img->img);
}

void    load_textures(t_setup *setup)
{
    char    *paths[4];
    int     i;
    t_img   img;

    // change this later
    paths[0] = setup->map->NO;
    paths[1] = setup->map->SO;
    paths[2] = setup->map->WE;
    paths[3] = setup->map->EA;
    i = 0;
    while (i < 4)
    {
        load_image(setup, paths[i], &img, i);
        i++;
    }
}