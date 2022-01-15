#include "../cub3D.h"

int setup_player(t_map *config, char char_for_check, int x_i, int y_i)
{
    if (config->player.angle != -1)
        return (-1);
    else
    {
        if (char_for_check == 'N')
            config->player.angle = ANGLE270;
        if (char_for_check == 'S')
            config->player.angle = ANGLE90;
        if (char_for_check == 'E')
            config->player.angle = ANGLE0;
        if (char_for_check == 'W')
            config->player.angle = ANGLE180;
        config->player.x = x_i * TILE_SIDE + TILE_SIDE / 2;
        config->player.y = y_i * TILE_SIDE + TILE_SIDE / 2;
    }
    return (0);
}

int is_player_setted(t_map *config)
{
    if (config->player.angle == -1)
    {
        printf("no player position\n");
        return (-1);
    }
    if (0 == (config->player.y - TILE_SIDE / 2) / TILE_SIDE
                || config->map_size - 1 == (config->player.y - TILE_SIDE / 2) / TILE_SIDE)
    {
        printf("player position on border\n");
        return (-1);
    }
    return (0);
}

