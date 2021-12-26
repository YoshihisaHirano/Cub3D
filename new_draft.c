#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
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
	double	sin[ANGLE360 + 1];
	double	inv_sin[ANGLE360 + 1];
	double	cos[ANGLE360 + 1];
	double	inv_cos[ANGLE360 + 1];
	double	tan[ANGLE360 + 1];
	double	inv_tan[ANGLE360 + 1];
	double	fish_table[ANGLE60 + 1];
	double	x_step_table[ANGLE360 + 1];
	double	y_step_table[ANGLE360 + 1];
}	t_trig_tables;

typedef	struct s_player {
	int	x;
	int	y;
	int	angle;
} t_player;

typedef struct s_point {
	int	x;
	int	y;
} t_point;


double	angle_to_radians(double angle)
{
	return (angle * M_PI/(double)ANGLE180);
}

bool	facing_down(int angle)
{
	if (angle >= ANGLE0 && angle < ANGLE180)
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
		tables->sin[i] = sin(rad);
		tables->inv_sin[i] = 1.0 / tables->sin[i];
		tables->cos[i] = cos(rad);
		tables->inv_cos[i] = 1.0 / cos(rad);
		tables->tan[i] = tan(rad);
		tables->inv_tan[i] = 1.0 / tables->tan[i];
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
		tables->x_step_table[i] = TILE_SIZE / tables->tan[i];
		if ((facing_left(i) && tables->x_step_table[i] > 0) ||
				(! facing_left(i) && tables->x_step_table[i] < 0))
			tables->x_step_table[i] *= -1;
		tables->y_step_table[i] = TILE_SIZE * tables->tan[i];
		if ((facing_down(i) && tables->y_step_table[i] < 0) ||
				(! facing_down(i) && tables->y_step_table[i]) > 0)
			tables->y_step_table[i] *= -1;
		i++;
	}
}

int	get_start_angle(int player_angle)
{
	int	start_angle;

	start_angle = player_angle - ANGLE30;
	if (start_angle < 0)
		start_angle += ANGLE360;
	return (start_angle);
}

double	dst_to_horizontal(t_trig_tables *tables, t_player *player, char **map, int curr_angle)
{
	t_point	first_intersec;
	t_point	current_pos;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE0 || curr_angle == ANGLE180)
		return (INT_MAX);
	if (facing_down(curr_angle))
	{
		first_intersec.y = (int)(player->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		deltas.y = TILE_SIZE;
	}
	else
	{
		first_intersec.y = (int)(player->y / TILE_SIZE) * TILE_SIZE - 1;
		deltas.y = -TILE_SIZE;
	}
	first_intersec.x = tables->tan[curr_angle] * (first_intersec.y - player->y) + player->x;
	
}