#include "../cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0)
	{
		dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_column(t_img *img, t_point coords, int height, int color)
{
	int i;

	i = 0;
	while (i < height)
	{
		my_pix_put(img, (int)coords.x, (int)coords.y + i, color);
		i++;
	}
}

void	draw_rectangle(t_img *img, t_rectangle *params, int color)
{
	int i;
	int j;

	i = 0;
	while (i < params->height)
	{
		j = 0;
		while (j < params->width)
		{
			my_pix_put(img, params->x + j, params->y + i, color);
			j++;
		}
		i++;
	}
}