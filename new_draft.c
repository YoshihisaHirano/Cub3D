#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "cub3D.h"
#define TILE_SIDE 64
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
#define PLAYER_HEIGHT (TILE_SIDE / 2)
#define PLANE_CENTER (PLANE_HEIGHT / 2)
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

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
	double	x;
	double	y;
} t_point;

void	draw_column(t_img *img, int x, int y, int height);

double	angle_to_radians(int angle)
{
	return ((angle * M_PI)/(double)ANGLE180);
}

bool	facing_down(int angle)
{
	if (angle >= ANGLE0 && angle <= ANGLE180)
		return true;
	return false;
}

bool	facing_left(int angle)
{
	if (angle >= ANGLE90 && angle <= ANGLE270)
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
		tables->x_step_table[i] = TILE_SIDE / tables->tan[i];
		if ((facing_left(i) && tables->x_step_table[i] > 0) ||
				(! facing_left(i) && tables->x_step_table[i] < 0))
			tables->x_step_table[i] *= -1;
		tables->y_step_table[i] = TILE_SIDE * tables->tan[i];
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

double	dst_to_horizontal(t_trig_tables *tables, t_player *player, char *map, int curr_angle)
{
	t_point	intersec;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE0 || curr_angle == ANGLE180)
		return (INT_MAX);
	deltas.y = TILE_SIDE;
	if (facing_down(curr_angle))
		intersec.y = ((int)(player->y / TILE_SIDE)) * TILE_SIDE + TILE_SIDE;
	else
	{
		intersec.y = ((int)(player->y / TILE_SIDE)) * TILE_SIDE - 1;
		deltas.y *= -1;
	}
	intersec.x = tables->inv_tan[curr_angle] * (intersec.y - player->y) + player->x;
	deltas.x = tables->x_step_table[curr_angle];
	while (true)
	{
		grid_idx.x = (int)(intersec.x / TILE_SIDE);
		grid_idx.y = (int)(intersec.y / TILE_SIDE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= MAP_WIDTH || grid_idx.y >= MAP_HEIGHT)
					return (INT_MAX);
		int map_index = (int)(grid_idx.y * MAP_WIDTH + grid_idx.x);
		if (map[map_index] != 'O')
			return ((intersec.x - player->x) * tables->inv_cos[curr_angle]);
		intersec.x += deltas.x;
		intersec.y += deltas.y;
	}
}

double dst_to_vertical(t_trig_tables *tables, t_player *player, char *map, int curr_angle)
{
	t_point	intersec;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE90 || curr_angle == ANGLE270)
		return (INT_MAX);
	deltas.x = TILE_SIDE;
	if (facing_left(curr_angle))
	{
		intersec.x = ((int)(player->x / TILE_SIDE)) * TILE_SIDE - 1;
		deltas.x *= -1;
	}
	else
		intersec.x = ((int)(player->x / TILE_SIDE)) * TILE_SIDE + TILE_SIDE;
	intersec.y = tables->tan[curr_angle] * (intersec.x - player->x) + player->y;
	deltas.y = tables->y_step_table[curr_angle];
	while (true)
	{
		grid_idx.x = (int)(intersec.x / TILE_SIDE);
		grid_idx.y = (int)(intersec.y / TILE_SIDE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= MAP_WIDTH || grid_idx.y >= MAP_HEIGHT)
			return (INT_MAX);
		if (map[(int)(grid_idx.y * MAP_WIDTH + grid_idx.x)] != 'O')
			return ((intersec.y - player->y) * tables->inv_sin[curr_angle]);
		intersec.x += deltas.x;
		intersec.y += deltas.y;
	}
}

int	normalize_height(int height)
{
	if (height < 0)
		return 0;
	if (height > PLANE_HEIGHT)
		return PLAYER_HEIGHT - 1;
	return height;
}

void    init_win(t_win *win)
{
	win->mlx_ptr = mlx_init();
	win->height = PLANE_HEIGHT;
	win->width = PLANE_WIDTH;
	win->win_ptr = mlx_new_window(win->mlx_ptr,
								  win->width, win->height, "Cub3D");
}

void    init_img(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
								  &(img->line_len), &(img->endian));
}

int main()
{
	t_player player;
	t_trig_tables	*tables;
	t_win win;
	t_img img;

	char map[] = {
	'W','W','W','W','W','W','W','W','W','W','W','W',
	'W','O','W','O','O','O','O','O','O','O','O','W',
	'W','O','W','O','O','O','O','O','O','O','O','W',
	'W','O','O','O','O','O','O','O','O','O','O','W',
	'W','W','O','O','O','O','O','O','O','O','O','W',
	'W','O','O','O','O','O','O','O','O','O','O','W',
	'W','O','W','O','O','O','O','O','O','O','O','W',
	'W','W','W','W','W','W','W','W','W','W','W','W'
};

	init_win(&win);
	init_img(&img, &win);
	player.x = 256;
	player.y = 67;
	player.angle = ANGLE90;
	tables = create_trig_tables();
	add_step_tables(tables);
	add_fish_table(tables);
	// printf("%d - ANGLE90 and in rads - %lf\n", ANGLE90, angle_to_radians(ANGLE90));
	int column = 0;
	int curr_angle = player.angle - ANGLE30;
	if (curr_angle < 0)
		curr_angle += ANGLE360;
	while (column < PLANE_WIDTH)
	{
		double	dist;
		int	wall_height;
		int wall_top;
		int wall_bottom;
		double h_dst = dst_to_horizontal(tables, &player, map, curr_angle);
		double v_dst = dst_to_vertical(tables, &player, map, curr_angle);
//		if (h_dst < 0)
//		{
//			printf("horizontal dst - %lf, vertical dst - %lf\n", h_dst, v_dst);
//			printf("%d - curr_angle, %lf - inverted tan, %lf - Xstep, %lf - "
//				   "angle in rads\n",
//				   curr_angle, tables->inv_tan[curr_angle],
//				   tables->x_step_table[curr_angle], angle_to_radians(curr_angle));
//		}
		dist = h_dst;
		if (v_dst < h_dst)
			dist = v_dst;
		dist /= tables->fish_table[column];
		// var projectedWallHeight=(this.WALL_HEIGHT*this.fPlayerDistanceToTheProjectionPlane/dist);
		wall_height = (int)(TILE_SIDE * PLAYER_PLANE_DST / dist);
		//topOfWall = this.fProjectionPlaneYCenter-(projectedWallHeight*0.5);
		wall_top = (int)(PLANE_CENTER - (wall_height / 2));
		if (wall_top < 0)
			wall_top = 0;
		// bottomOfWall = this.fProjectionPlaneYCenter+(projectedWallHeight*0.5);
		wall_bottom = (int)(PLANE_CENTER + (wall_height / 2));
		if (wall_bottom > PLANE_HEIGHT)
			wall_bottom = PLANE_HEIGHT - 1;
		draw_column(&img, column, wall_top, wall_bottom - wall_top + 1);
		column++;
		curr_angle++;
		if (curr_angle > ANGLE360)
			curr_angle -= ANGLE360;
	}
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.img, 0, 0);
	mlx_loop(win.mlx_ptr);
	return (0);
}