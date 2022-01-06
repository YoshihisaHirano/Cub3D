/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:54:12 by aalannys            #+#    #+#           */
/*   Updated: 2022/01/06 13:54:12 by aalannys            ###    #######.fr    */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

char my_map[] = {
		'W','W','W','W','W','W','W','W','W','W','W','W',
		'W','O','W','O','O','O','O','O','O','O','O','W',
		'W','O','W','O','O','O','O','O','O','O','O','W',
		'W','O','O','O','O','O','O','O','O','O','O','W',
		'W','W','O','O','O','O','O','O','O','O','O','W',
		'W','O','O','O','O','O','O','O','O','O','O','W',
		'W','O','W','O','O','O','O','O','O','O','O','W',
		'W','W','W','W','W','W','W','W','W','W','W','W'
};

void    init_win(t_win *win)
{
	win->mlx_ptr = mlx_init();
	win->height = PLANE_HEIGHT;
	win->width = PLANE_WIDTH;
	win->win_ptr = mlx_new_window(win->mlx_ptr,
								  win->width, win->height, "Cub3D");
}

void    init_img(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
								  &(img->line_len), &(img->endian));
}

t_config	*create_config()
{
	t_config		*config;
	t_player		*player;
	t_trig_tables	*tables;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL); //handle this
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL); //handle this
	//map will be different when parser is ready
	config->map = my_map;
	config->player = player;
	// player's params will be taken from the map
	config->player->x = 160;
	config->player->y = 160;
	config->player->angle = ANGLE60;
	tables = create_trig_tables();
	add_step_tables(tables);
	add_fish_table(tables);
	config->tables = tables;
	return (config);
}