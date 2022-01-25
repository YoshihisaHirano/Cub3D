#include "../cub3D.h"

void	set_player_NS(t_map *config, char char_for_check)
{
	if (char_for_check == 'N')
	{
		config->player->dir->x = 0.0;
		config->player->dir->y = -1.0;
		config->plane->x = FOV;
		config->plane->y = 0.0;
	}
	if (char_for_check == 'S')
	{
		config->player->dir->x = 0.0;
		config->player->dir->y = 1.0;
		config->plane->x = -FOV;
		config->plane->y = 0.0;
	}
}

void	set_player_EW(t_map *config, char char_for_check)
{
	if (char_for_check == 'E')
	{
		config->player->dir->x = 1.0;
		config->player->dir->y = 0.0;
		config->plane->x = 0.0;
		config->plane->y = FOV;
	}
	if (char_for_check == 'W')
	{
		config->player->dir->x = -1.0;
		config->player->dir->y = 0.0;
		config->plane->x = 0.0;
		config->plane->y = -FOV;
	}
}

int setup_player(t_map *config, char char_for_check, int x_i, int y_i)
{
	if (config->player->pos->x != -1)
		return (-1);
	if (char_for_check == 'N' || char_for_check == 'S')
		set_player_NS(config, char_for_check);
	else if (char_for_check == 'E' || char_for_check == 'W')
		set_player_EW(config, char_for_check);
	config->player->pos->x = x_i + 0.5;
	config->player->pos->y = y_i + 0.5;
	return (0);
}

int is_player_setted(t_map *config)
{
	int player_x;
	int player_y;

	player_x = config->player->pos->x - 0.5;
	player_y = config->player->pos->y - 0.5;
	if (player_x == -1 || player_x == -1)
	{
		printf("Error\nNo player position\n");
		return (-1);
	}
	if (player_y == 0 || player_x == 0
		|| config->map[player_y - 1][player_x] == ' '
		|| config->map[player_y + 1][player_x] == ' '
		|| config->map[player_y][player_x - 1] == ' '
		|| config->map[player_y][player_x + 1] == ' ')
	{
		printf("Error\nPlayer position on border\n");
		return (-1);
	}
	return (0);
}

int check_top_bottom_borders(t_map *config)
{
	int     x_i;

	x_i = 0;
	while (x_i <= config->max_line)
	{
		if (config->map[0][x_i] == '0'
			|| config->map[config->map_size - 1][x_i] == '0')
			return (-1);
		x_i++;
	}
	return (0);
}