#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TILE_SIZE 64
#define PLANE_WIDTH 320
#define PLANE_HEIGHT 200
/* angles */
#define ANGLE60 PLANE_WIDTH
#define ANGLE30 (ANGLE60 / 2)
#define ANGLE90 (ANGLE30 * 3)
#define ANGLE180 (ANGLE90 * 2)
#define ANGLE270 (ANGLE90 * 3)
#define ANGLE360 (ANGLE60 * 6)
#define ANGLE0 0
#define ANGLE5 (ANGLE30 / 5)
#define ANGLE10 (ANGLE5 * 2)
/* player's attributes */
#define PLAYER_X 100
#define PLAYER_Y 160
#define PLAYER_ANGLE ANGLE0
#define PLAYER_PLANE_DST 277
#define PLAYER_HEIGHT (TILE_SIZE / 2)
#define PLANE_CENTER (PLAYER_HEIGHT / 2)

typedef struct s_trig_tables {
	double	sin_table[ANGLE360 + 1];
	double	inv_sin_table[ANGLE360 + 1];
	double	cos_table[ANGLE360 + 1];
	double	inv_cos_table[ANGLE360 + 1];
	double	tan_table[ANGLE360 + 1];
	double	inv_tan_table[ANGLE360 + 1];
	double	fish_table[ANGLE60 + 1];
	double	x_step_table[ANGLE360 + 1];
	double	y_step_table[ANGLE360 + 1];
}	t_trig_tables;

double	angle_to_radians(double angle)
{
	return (angle * M_PI/(double)ANGLE180);
}

bool	facing_down(int angle)
{
	if (angle >= ANGLE0 && angle <= ANGLE180)
		return true;
	return false;
}

bool	facing_left(int angle)
{
	if (angle >= ANGLE90 && angle < ANGLE270)
		return true;
	return false;
}

t_trig_tables	*create_trig_tables(void)
{
	int				i;
	double			rad;
	t_trig_tables	*tables;

	i = 0;
	tables = malloc(sizeof(t_trig_tables));
	if (!tables)
		return NULL; // <3 amatilda; will need to handle this
	while (i <= ANGLE360)
	{
		rad = angle_to_radians(i) + 0.0001; // addition to avoid zero division
		tables->sin_table[i] = sin(rad);
		tables->inv_sin_table[i] = 1.0 / tables->sin_table[i];
		tables->cos_table[i] = cos(rad);
		tables->inv_cos_table[i] = 1.0 / cos(rad);
		tables->tan_table[i] = tan(rad);
		tables->inv_tan_table[i] = 1.0 / tables->tan_table[i];
		i++;
	}
	return (tables);
}

void	add_fish_table(t_trig_tables *tables)
{
	int	i;

	i = -ANGLE30;
	while (i <= ANGLE30)
	{
		tables->fish_table[i + ANGLE30] = 1.0 / cos(angle_to_radians(i));
		i++;
	}
}

void	add_step_tables(t_trig_tables *tables)
{
	int	i;

	i = 0;
	while (i <= ANGLE360)
	{
		tables->x_step_table[i] = TILE_SIZE / tables->tan_table[i];
		if ((facing_left(i) && tables->x_step_table[i] > 0) ||
				(! facing_left(i) && tables->x_step_table[i] < 0))
			tables->x_step_table[i] *= -1;
		tables->y_step_table[i] = TILE_SIZE * tables->tan_table[i];
		i++;
	}
}