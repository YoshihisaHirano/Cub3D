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

	h_dst = dst_to_horizontal(setup, angle);
	v_dst = dst_to_vertical(setup, angle);
	// v_dst = floor(v_dst / setup->tables->fish_table[column]);
	// h_dst = floor(h_dst / setup->tables->fish_table[column]);
	if (column == 17) printf("%.10lf - h_dst, %.10lf - v_dst\n", h_dst, v_dst);
	if (h_dst > v_dst)
	{
		setup->col->vertical_hit = true;
		return (v_dst / setup->tables->fish_table[column]);
	}
	setup->col->vertical_hit = false;
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
	// printf("%lf - pos.x, %lf - pos.y, %lf - dir.x, %lf - dir.y\n", setup->player->pos->x, setup->player->pos->y, setup->player->dir->x, setup->player->dir->y);
	while (column < PLANE_WIDTH)
	{
		col = (t_column){ 0 };
		col.no = column;
		render(setup);
		column += 1;
		curr_angle += 1;
		if (curr_angle >= ANGLE360)
			curr_angle -= ANGLE360;
	}
}