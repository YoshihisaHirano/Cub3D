#ifndef UTILS_H
# define UTILS_H
# include <math.h>
# include "../cub3D.h"

/* draw */
void	draw_column(t_img *img, int x, int y, int height);
/* math */
double  angle_in_radians(int angle_in_degrees);
int bitwise_division(int divident, int divisor);

#endif