/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:55:09 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 17:55:09 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3D.h"

double find_dst(t_setup *setup, int angle, int column)
{
	double	h_dst;
	double	v_dst;

	h_dst = dst_to_horizontal(setup->tables, setup->player, setup->map, angle);
	v_dst = dst_to_vertical(setup->tables, setup->player, setup->map, angle);
//	 if (column == 160)
//	 {
//	 	printf("%d - angle, %lf - h_dst, %lf - v_dst\n", angle, h_dst, v_dst);
//	 }
	if (v_dst < h_dst)
		return (v_dst / setup->tables->fish_table[column]);
	return (h_dst / setup->tables->fish_table[column]);
}

int	wall_height(double dist)
{
	return (floor(TILE_SIDE * PLAYER_PLANE_DST / dist));
}

void	find_draw_column(t_setup *setup, int curr_angle, int column)
{
	double		dist;
	int			wall_top;
	int			wall_bottom;
	t_rectangle	rect;
	int			color;

	dist = find_dst(setup, curr_angle, column);
//	 printf("%d - column, %d - wall height\n", column, wall_height(dist));
	wall_top = floor(PLANE_CENTER - (wall_height(dist) / 2));
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = floor(PLANE_CENTER + (wall_height(dist) / 2));
	if (wall_bottom > PLANE_HEIGHT)
		wall_bottom = PLANE_HEIGHT - 1;
	rect.x = column;
	rect.y = wall_top;
	rect.height = (wall_bottom - wall_top + 1);
	rect.width = 1;
	color = create_trgb(0, 150, 75, 0); // arbitrary color for now
	draw_rectangle(setup->image, &rect, color);
}

void	draw_floor_ceil(t_setup *setup)
{
	t_rectangle	floor;
	t_rectangle	ceil;

	floor.x = 0;
	floor.y = PLANE_CENTER;
	floor.width = PLANE_WIDTH;
	floor.height = PLANE_CENTER;
	ceil.x = 0;
	ceil.y = 0;
	ceil.width = PLANE_WIDTH;
	ceil.height = PLANE_CENTER;
	draw_rectangle(setup->image, &floor, setup->map->floor_color);
	draw_rectangle(setup->image, &ceil, setup->map->ceil_color);
}

void	draw_plane(t_setup *setup)
{
	int	column;
	int	curr_angle;

	column = 0;
	curr_angle = setup->player->angle - ANGLE30;
	if (curr_angle < 0)
		curr_angle += ANGLE360;
	draw_floor_ceil(setup);
	while (column < PLANE_WIDTH)
	{
		find_draw_column(setup, curr_angle, column);
		column += 1;
		curr_angle += 1;
		if (curr_angle >= ANGLE360)
			curr_angle -= ANGLE360;
	}
}