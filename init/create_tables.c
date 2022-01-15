/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:30:55 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 12:30:55 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3D.h"

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

bool	face_left(int angle)
{
	return (angle >= ANGLE90 && angle < ANGLE270);
}

bool	face_down(int angle)
{
	return (angle >= ANGLE0 && angle < ANGLE180);
}

void	add_step_tables(t_trig_tables *tables)
{
	int	i;

	i = 0;
	while (i <= ANGLE360)
	{
		tables->x_step_table[i] = TILE_SIDE / tables->tan[i];
		if ((face_left(i) && tables->x_step_table[i] > 0) ||
			((!face_left(i)) && tables->x_step_table[i] < 0))
			tables->x_step_table[i] *= -1;
		tables->y_step_table[i] = TILE_SIDE * tables->tan[i];
		if ((face_down(i) && tables->y_step_table[i] < 0) ||
			((!face_down(i)) && tables->y_step_table[i] > 0))
			tables->y_step_table[i] *= -1;
		i++;
	}
}

t_trig_tables	*create_trig_tables(void)
{
	int				i;
	double			rad;
	t_trig_tables	*tables;

	i = 0;
	tables = malloc(sizeof(t_trig_tables));
	if (!tables)
		error_exit(MEM_ALLOC_ERR);
	while (i <= ANGLE360)
	{
		rad = angle_to_radians(i) + 0.0001;
		tables->sin[i] = sin(rad);
		tables->inv_sin[i] = 1.0 / tables->sin[i];
		tables->cos[i] = cos(rad);
		tables->inv_cos[i] = 1.0 / cos(rad);
		tables->tan[i] = tan(rad);
		tables->inv_tan[i] = 1.0 / tables->tan[i];
		i++;
	}
	add_step_tables(tables);
	add_fish_table(tables);
	return (tables);
}
