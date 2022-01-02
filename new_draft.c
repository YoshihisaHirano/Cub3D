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

double	angle_to_radians(double angle)
{
	return (angle * M_PI/(double)ANGLE180);
}

bool	facing_down(int angle)
{
	if (angle > ANGLE0 && angle < ANGLE180)
		return true;
	return false;
}

bool	facing_left(int angle)
{
	if (angle > ANGLE90 && angle < ANGLE270)
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

double	dst_to_horizontal(t_trig_tables *tables, t_player *player, char *map, int curr_angle)
{
	t_point	intersec;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE0 || curr_angle == ANGLE180)
		return (INT_MAX);
	//        if (castArc==ANGLE0 || castArc==ANGLE180)
//        {
//          distToHorizontalGridBeingHit=9999999F;//Float.MAX_VALUE;
//        }
	deltas.y = TILE_SIZE;
	//          distToNextHorizontalGrid = TILE_SIZE;
	if (facing_down(curr_angle))
		intersec.y = ((int)(player->y / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
		//          horizontalGrid = (fPlayerY/TILE_SIZE)*TILE_SIZE  + TILE_SIZE;
	else
	{
		intersec.y = ((int)(player->y / TILE_SIZE)) * TILE_SIZE - 1;
		//          horizontalGrid = (fPlayerY/TILE_SIZE)*TILE_SIZE;
		//          horizontalGrid--;
		deltas.y *= -1;
		//          distToNextHorizontalGrid = -TILE_SIZE;
	}
	intersec.x = tables->inv_tan[curr_angle] * (intersec.y - player->y) + player->x;
	//          xIntersection = xtemp + fPlayerX;
//          float xtemp = fITanTable[castArc]*(horizontalGrid - fPlayerY);
	deltas.x = tables->x_step_table[curr_angle];
	//          distToNextXIntersection = fXStepTable[castArc];
	while (true)
	{
		grid_idx.x = (int)(intersec.x / TILE_SIZE);
		//            xGridIndex = (int)(xIntersection/TILE_SIZE);
		grid_idx.y = (int)(intersec.y / TILE_SIZE);
//            yGridIndex = (horizontalGrid/TILE_SIZE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= MAP_WIDTH || grid_idx.y >= MAP_HEIGHT)
					return (INT_MAX);
		//            if ((xGridIndex>=MAP_WIDTH) ||
//              (yGridIndex>=MAP_HEIGHT) ||
//              xGridIndex<0 || yGridIndex<0)
//            {
//              distToHorizontalGridBeingHit = Float.MAX_VALUE;
//              break;
//            }
		int map_index = (int)(grid_idx.y * MAP_WIDTH + grid_idx.x);
		if (map[map_index] != 'O')
			return ((intersec.x - player->x) * tables->inv_cos[curr_angle]);
		//            else if ((fMap[yGridIndex*MAP_WIDTH+xGridIndex])!=O)
//            {
//              distToHorizontalGridBeingHit  = (xIntersection-fPlayerX)*fICosTable[castArc];
//              break;
//            }
		intersec.x += deltas.x;
		intersec.y += deltas.y;
		//              xIntersection += distToNextXIntersection;
//              horizontalGrid += distToNextHorizontalGrid;
	
	}
}

// // FOLLOW X RAY
//        if (castArc < ANGLE90 || castArc > ANGLE270)
//        {



//          float ytemp = fTanTable[castArc]*(verticalGrid - fPlayerX);
//          yIntersection = ytemp + fPlayerY;
//        }
//        // RAY FACING LEFT
//        else
//        {





//        }
//            // LOOK FOR VERTICAL WALL

//        else
//        {

//          while (true)
//          {
//            // compute current map position to inspect



//            else if ((fMap[yGridIndex*MAP_WIDTH+xGridIndex])!=O)
//            {
//              distToVerticalGridBeingHit =(yIntersection-fPlayerY)*fISinTable[castArc];
//              break;
//            }
//            else
//            {

//            }
//          }
//        }

double dst_to_vertical(t_trig_tables *tables, t_player *player, char *map, int curr_angle)
{
	t_point	intersec;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE90 || curr_angle == ANGLE270)
		return (INT_MAX);
	//        if (castArc==ANGLE90||castArc==ANGLE270)
//        {
//          distToVerticalGridBeingHit = 9999999;//Float.MAX_VALUE;
//        }
	deltas.x = TILE_SIZE;
	//          distToNextVerticalGrid = TILE_SIZE;
	if (curr_angle >= 90 || curr_angle <= 270)
	{
		intersec.x = ((int)(player->x / TILE_SIZE)) * TILE_SIZE - 1;
		//          verticalGrid = (fPlayerX/TILE_SIZE)*TILE_SIZE;
		//          verticalGrid--;
		deltas.x *= -1;
		//          distToNextVerticalGrid = -TILE_SIZE;
	}
	else
		intersec.x = ((int)(player->x / TILE_SIZE)) * TILE_SIZE + TILE_SIZE;
		//          verticalGrid = TILE_SIZE + (fPlayerX/TILE_SIZE)*TILE_SIZE;
	intersec.y = tables->tan[curr_angle] * (intersec.x - player->x) + player->y;
//          float ytemp = fTanTable[castArc]*(verticalGrid - fPlayerX);
//          yIntersection = ytemp + fPlayerY;
	deltas.y = tables->y_step_table[curr_angle];
	//          distToNextYIntersection = fYStepTable[castArc];
	while (true)
	{
		grid_idx.x = (int)(intersec.x / TILE_SIZE);
		grid_idx.y = (int)(intersec.y / TILE_SIZE);
		//            xGridIndex = (verticalGrid/TILE_SIZE);
//            yGridIndex = (int)(yIntersection/TILE_SIZE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= MAP_WIDTH || grid_idx.y >= MAP_HEIGHT)
			return (INT_MAX);
		//            if ((xGridIndex>=MAP_WIDTH) ||
//              (yGridIndex>=MAP_HEIGHT) ||
//              xGridIndex<0 || yGridIndex<0)
//            {
//              distToVerticalGridBeingHit = Float.MAX_VALUE;
//              break;
//            }
		if (map[(int)(grid_idx.y * MAP_WIDTH + grid_idx.x)] != 'O')
			return ((intersec.y - player->y) * tables->inv_sin[curr_angle]);
			//            else if ((fMap[yGridIndex*MAP_WIDTH+xGridIndex])!=O)
//            {
//              distToVerticalGridBeingHit =(yIntersection-fPlayerY)*fISinTable[castArc];
//              break;
//            }
		intersec.x += deltas.x;
		intersec.y += deltas.y;
		//              yIntersection += distToNextYIntersection;
//              verticalGrid += distToNextVerticalGrid;
		// printf("grid position (vertical) %lf - x, %lf - y\n", intersec.x, intersec.y);
	}
}

int main()
{
	t_player player;
	t_trig_tables	*tables;

	char map[] = {
	'W','W','W','W','W','W','W','W','W','W','W','W',
	'W','O','O','O','O','O','O','O','O','O','O','W',
	'W','O','O','O','O','O','O','O','O','O','O','W',
	'W','O','O','O','O','O','O','O','W','O','O','W',
	'W','O','O','W','O','W','O','O','W','O','O','W',
	'W','O','O','W','O','W','W','O','W','O','O','W',
	'W','O','O','W','O','O','W','O','W','O','O','W',
	'W','O','O','O','W','O','W','O','W','O','O','W',
	'W','O','O','O','W','O','W','O','W','O','O','W',
	'W','O','O','O','W','W','W','O','W','O','O','W',
	'W','O','O','O','O','O','O','O','O','O','O','W',
	'W','W','W','W','W','W','W','W','W','W','W','W'
};

	player.x = 67;
	player.y = 67;
	player.angle = ANGLE90;
	tables = create_trig_tables();
	add_step_tables(tables);
	add_fish_table(tables);
	// printf("%d - ANGLE90 and in rads - %lf\n", ANGLE90, angle_to_radians(ANGLE90));
	int i = 0;
	int curr_angle = player.angle - ANGLE30;
	if (curr_angle < 0)
		curr_angle += ANGLE360;
	while (i < PLANE_WIDTH)
	{
		double h_dst = dst_to_horizontal(tables, &player, map, curr_angle);
		double v_dst = dst_to_vertical(tables, &player, map, curr_angle);
		printf("horizontal dst - %lf, vertical dst - %lf\n", h_dst, v_dst);
		i += 5;
		curr_angle += 5;
		if (curr_angle > ANGLE360)
			curr_angle -= ANGLE360;
	}
	return (0);
}