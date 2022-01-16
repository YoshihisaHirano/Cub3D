/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_horizontal.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:55:09 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 17:55:09 by aalannys            ###    #######.fr    */
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

double	get_h_distance(t_setup *setup, int arc, t_point *intersec, t_point *deltas)
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
            setup->col->h_intersec.y = intersec->y;
			setup->col->h_intersec.x = intersec->x;
            return ((intersec->x - setup->player->x) * setup->tables->inv_cos[arc]);
        }
		intersec->x += deltas->x;
		intersec->y += deltas->y;
	}
}

double	dst_to_horizontal(t_setup *setup, int curr_angle)
{
	t_point	intersec;
	t_point	deltas;

	if (curr_angle == ANGLE0 || curr_angle == ANGLE180)
		return (INT_MAX);
	deltas.y = TILE_SIDE;
	if (! facing_down(curr_angle))
		deltas.y *= -1;
	deltas.x = setup->tables->x_step_table[curr_angle];
	intersec = find_first_horizontal(setup->player, curr_angle, setup->tables);
    return (get_h_distance(setup, curr_angle, &intersec, &deltas));
}