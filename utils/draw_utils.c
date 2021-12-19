#include "utils.h"

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

void	draw_column(t_img *img, int x, int y, int height)
{
	int i;
	int	color;

	i = 0;
	color = create_trgb(0, 3, 19, 242); // arbitrary blue color
	while (i < height)
	{
		my_pix_put(img, x, y + i, color);
		i++;
	}
}
