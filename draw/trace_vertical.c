/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_vertical.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:05:20 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 13:05:20 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3D.h"

t_point	find_first_vertical(t_player *player, int curr_angle, t_trig_tables *tables)
{
	t_point	intersec;

	if (facing_right(curr_angle))
		intersec.x = floor(player->x / TILE_SIDE) * TILE_SIDE + TILE_SIDE;
	else
		intersec.x = floor(player->x / TILE_SIDE) * TILE_SIDE - 1;
	intersec.y = tables->tan[curr_angle] * (intersec.x - player->x) + player->y;
	return (intersec);
}

double	get_v_distance(t_setup *setup, int arc, t_point *intersec, t_point *deltas)
{
	t_point	grid_idx;

	while (true)
	{
		grid_idx.x = floor(intersec->x / TILE_SIDE);
		grid_idx.y = floor(intersec->y / TILE_SIDE);
		if (ray_out_of_map(setup->map, &grid_idx))
			return (INT_MAX);
		if (check_wall(setup->map, grid_idx.x, grid_idx.y))
		{
			setup->col->v_intersec.y = intersec->y;
			setup->col->v_intersec.x = intersec->x;
			return ((intersec->y - setup->player->y) * setup->tables->inv_sin[arc]);
		}
		intersec->x += deltas->x;
		intersec->y += deltas->y;
	}
}

double dst_to_vertical(t_setup *setup, int curr_angle)
{
	t_point	intersec;
	t_point	deltas;

	if (curr_angle == ANGLE90 || curr_angle == ANGLE270)
		return (INT_MAX);
	deltas.x = TILE_SIDE;
	if (!facing_right(curr_angle))
		deltas.x *= -1;
	deltas.y = setup->tables->y_step_table[curr_angle];
	intersec = find_first_vertical(setup->player, curr_angle, setup->tables);
	return (get_v_distance(setup, curr_angle, &intersec, &deltas));
}