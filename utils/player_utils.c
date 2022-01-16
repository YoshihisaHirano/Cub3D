/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:33:42 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 12:33:42 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3D.h"

double	angle_to_radians(int angle)
{
	return ((angle * M_PI)/(double)ANGLE180);
}

bool	facing_down(int angle)
{
	return (angle > ANGLE0 && angle < ANGLE180);
}

bool	facing_right(int angle)
{
	return (angle < ANGLE90 || angle > ANGLE270);
}

int	get_start_angle(int player_angle)
{
	int	start_angle;

	start_angle = player_angle - ANGLE30;
	if (start_angle < 0)
		start_angle += ANGLE360;
	return (start_angle);
}

bool	ray_out_of_map(t_map *map, t_point *grid_coords)
{
	return (grid_coords->x < 0 || grid_coords->y < 0 ||
			grid_coords->x >= map->max_line || grid_coords->y >= map->map_size);
}
