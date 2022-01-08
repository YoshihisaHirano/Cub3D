/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:05:20 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 13:05:20 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3D.h"

t_point	find_first_horizontal(t_player *player, int curr_angle, t_trig_tables *tables)
{
	t_point	intersec;

	if (facing_down(curr_angle))
		intersec.y = floor(player->y / TILE_SIDE) * TILE_SIDE + TILE_SIDE;
	else
		intersec.y = floor(player->y / TILE_SIDE) * TILE_SIDE - 1;
	intersec.x = tables->inv_tan[curr_angle] * (intersec.y - player->y) + player->x;
	return (intersec);
}

double	dst_to_horizontal(t_trig_tables *tables, t_player *player, t_map *map, int curr_angle)
{
	t_point	grid_idx;
	t_point	intersec;
	t_point	deltas;

	if (curr_angle == ANGLE0 || curr_angle == ANGLE180)
		return (INT_MAX);
	deltas.y = TILE_SIDE;
	if (! facing_down(curr_angle))
		deltas.y *= -1;
	deltas.x = tables->x_step_table[curr_angle];
	intersec = find_first_horizontal(player, curr_angle, tables);
	while (true)
	{
		grid_idx.x = floor(intersec.x / TILE_SIDE);
		grid_idx.y = floor(intersec.y / TILE_SIDE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= MAP_WIDTH || grid_idx.y >= MAP_HEIGHT)
			return (INT_MAX);
		if (check_wall(map, grid_idx.x, grid_idx.y))
			return ((intersec.x - player->x) * tables->inv_cos[curr_angle]);
		intersec.x += deltas.x;
		intersec.y += deltas.y;
	}
}

t_point	find_first_vertical(t_player *player, int curr_angle, t_trig_tables *tables)
{
	t_point	intersec;

	if (facing_right(curr_angle))
		intersec.x = floor(player->x / TILE_SIDE) * TILE_SIDE + TILE_SIDE;
	else
		intersec.x = floor(player->x / TILE_SIDE) * TILE_SIDE - 1;
	intersec.y = tables->tan[curr_angle] * (intersec.x - player->x) + player->y;
//	if (curr_angle == 1441)
//	{
//		printf("%lf - intersec.y, %lf - intersec.x\n", intersec.y, intersec.x);
//	}
	return (intersec);
}

/*
 * intersec.x 384 intersec.y -18656.99112895755
 */

/*
 * castArc 1441 invSin -1.0000056868792673 yIntersection -18656.99112895755 distToVerticalGridBeingHit 1.7976931348623157e+308
 * deltaY -18976.99112895755 deltaX 64
 */

/*
 * 616.51548638996177942317 - Yintersec, 320 - playerY, -1.000006 - invSin 1441 - curr_angle, 0 - i
-18976.991129 - deltasY, -64.000000 - deltasX

 */

double dst_to_vertical(t_trig_tables *tables, t_player *player, t_map *map, int curr_angle)
{
	t_point	intersec;
	t_point	grid_idx;
	t_point	deltas;

	if (curr_angle == ANGLE90 || curr_angle == ANGLE270)
		return (INT_MAX);
	deltas.x = TILE_SIDE;
	if (!facing_right(curr_angle))
		deltas.x *= -1;
	deltas.y = tables->y_step_table[curr_angle];
	intersec = find_first_vertical(player, curr_angle, tables);
	int i = 0;
	while (true)
	{
		grid_idx.x = floor(intersec.x / TILE_SIDE);
		grid_idx.y = floor(intersec.y / TILE_SIDE);
		if (grid_idx.x < 0 || grid_idx.y < 0 ||
			grid_idx.x >= map->max_line || grid_idx.y >= map->map_size)
			return (INT_MAX);
		if (check_wall(map, grid_idx.x, grid_idx.y))
		{
			double res = ((intersec.y - player->y) *
					tables->inv_sin[curr_angle]);
//			if (curr_angle == 1441)
//			{
//				printf("%lf - res\n", res);
//				printf("%.20lf - Yintersec, %d - playerY, %lf - invSin %d - "
//					   "curr_angle, %d - i\n", intersec.y, player->y, tables->inv_sin[curr_angle], curr_angle, i);
//				printf("%lf - deltasY, %lf - deltasX\n", deltas.y, deltas.x);
//			}
			return (res);
		}
		intersec.x += deltas.x;
		intersec.y += deltas.y;
		i++;
	}
}