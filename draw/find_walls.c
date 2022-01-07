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
		intersec.y = ((int)(player->y / TILE_SIDE)) * TILE_SIDE + TILE_SIDE;
	else
		intersec.y = ((int) (player->y / TILE_SIDE)) * TILE_SIDE - 1;
	intersec.x = tables->inv_tan[curr_angle] * (intersec.y - player->y) + player->x;
	return (intersec);
}

double	dst_to_horizontal(t_trig_tables *tables, t_player *player, char *map, int curr_angle)
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

t_point	find_first_vertical(t_player *player, int curr_angle, t_trig_tables *tables)
{
	t_point	intersec;

	if (facing_left(curr_angle))
		intersec.x = ((int)(player->x / TILE_SIDE)) * TILE_SIDE - 1;
	else
		intersec.x = ((int)(player->x / TILE_SIDE)) * TILE_SIDE + TILE_SIDE;
	intersec.y = tables->tan[curr_angle] * (intersec.x - player->x) + player->y;
	return (intersec);
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
		deltas.x *= -1;
	deltas.y = tables->y_step_table[curr_angle];
	intersec = find_first_vertical(player, curr_angle, tables);
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