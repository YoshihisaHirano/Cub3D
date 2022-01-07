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
#include "../cub3D.h"

char *my_map = "WWWWWWWWWWWWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWOOOOOOOOOOWWWWWWWWWWWWW";

t_win	*init_win()
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	if (!win)
		error_exit(MEM_ALLOC_ERR);
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		error_exit(INIT_WIN_ERR);
	win->height = PLANE_HEIGHT;
	win->width = PLANE_WIDTH;
	win->win_ptr = mlx_new_window(win->mlx_ptr,
								  win->width, win->height, "Cub3D");
	return (win);
}

t_img	*init_img(t_win *win)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		error_exit(MEM_ALLOC_ERR);
	img->img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
								  &(img->line_len), &(img->endian));
	return (img);
}

t_setup	*create_setup()
{
	t_setup			*setup;
	t_player		*player;
	t_trig_tables	*tables;

	setup = malloc(sizeof(t_setup));
	if (!setup)
		error_exit(MEM_ALLOC_ERR);
	player = malloc(sizeof(t_player));
	if (!player)
		error_exit(MEM_ALLOC_ERR);
	//map will be different when parser is ready
	setup->map1 = my_map;
	setup->player = player;
	// players params will be taken from the map
	setup->player->x = PLAYER_X;
	setup->player->y = PLAYER_Y;
	setup->player->angle = PLAYER_ANGLE;
	tables = create_trig_tables();
	setup->tables = tables;
	return (setup);
}

t_setup	*init_all()
{
	t_setup		*setup;
	t_win		*win;
	t_img		*img;
	
	win = init_win();
	img = init_img(win);
	setup = create_setup();
	setup->image = img;
	setup->win = win;
	return (setup);
}
