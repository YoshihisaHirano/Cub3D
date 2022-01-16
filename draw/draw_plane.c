/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:55:09 by aalannys          #+#    #+#             */
/*   Updated: 2022/01/16 11:25:27 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double find_dst(t_setup *setup, int angle, int column)
{
	double	h_dst;
	double	v_dst;

	h_dst = dst_to_horizontal(setup, angle);
	v_dst = dst_to_vertical(setup, angle);
	if (v_dst < h_dst)
	{
		setup->col->vertical_hit = true;
		return (v_dst / setup->tables->fish_table[column]);
	}
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
	// int			color;

	dist = find_dst(setup, curr_angle, column);
	assign_wall_dir(setup->col, curr_angle);
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
	// call render tex column instead
	// color = create_trgb(0, 150, 75, 0); // arbitrary color for now
	// draw_rectangle(setup->image, &rect, color);
	render_tex_column(setup, wall_top, wall_bottom);
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
	int			column;
	int			curr_angle;
	t_column	col;

	column = 0;
	curr_angle = setup->player->angle - ANGLE30;
	setup->col = &col;
	if (curr_angle < 0)
		curr_angle += ANGLE360;
	draw_floor_ceil(setup);
	while (column < PLANE_WIDTH)
	{
		col = (t_column){ 0 };
		col.no = column;
		find_draw_column(setup, curr_angle, column);
		column += 1;
		curr_angle += 1;
		if (curr_angle >= ANGLE360)
			curr_angle -= ANGLE360;
	}
}