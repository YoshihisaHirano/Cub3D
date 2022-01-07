#include "../cub3D.h"

// empty lines at the end of file??? is it ok?? 
// close map

int check_filename(char *file_name)
{
    int len;

    len = ft_strlen(file_name);
    if (ft_strncmp(file_name + len - 4, ".cub", 5))
        return (-1);
    else
        return (0);
}

int check_map_for_sym(t_map *config, char **map)
{
    int     has_map_char;
    int     y_i;
    int     x_i;

    y_i = 0;
    while (map[y_i])
    {
        x_i = 0;
        has_map_char = 0;
        while (map[y_i][x_i])
        {
//            if (map[y_i][x_i] == 'N' || map[y_i][x_i] == 'S' || map[y_i][x_i] == 'E' || map[y_i][x_i] == 'W')
            if ( ft_strchr("NSEW", map[y_i][x_i]))
                if (config->player.angle != -1)
                    return (-1);
                else
                {
                    if (map[y_i][x_i] == 'N')
                        config->player.angle = ANGLE270;
                    if (map[y_i][x_i] == 'S')
                        config->player.angle = ANGLE90;
                    if (map[y_i][x_i] == 'E')
                        config->player.angle = ANGLE0;
                    if (map[y_i][x_i] == 'W')
                        config->player.angle = ANGLE180;
                    config->player.x = x_i * TILE_SIDE + TILE_SIDE / 2;
                    config->player.y = y_i * TILE_SIDE + TILE_SIDE / 2;
                }
            else if (map[y_i][x_i] != '0' && map[y_i][x_i] != '1' && map[y_i][x_i]  != ' ')
                        return (-1);
            if (has_map_char || map[y_i][x_i] == '0' || map[y_i][x_i] == '1' || map[y_i][x_i] == 'N'
                || map[y_i][x_i] == 'S' || map[y_i][x_i] == 'E' || map[y_i][x_i] == 'W')
                    has_map_char = 1;
            x_i++;
        }
        if (!has_map_char)
            return (-1);
        y_i++;
    }
    if (config->player.angle == -1)
        return (-1);
    return (0);
}

int check_borders(t_map *config)
{
    int     x_i;
    int     y_i;
    int     line_end_i;

    x_i = 0;
    while (x_i <= config->max_line)
    {
        if (config->map[0][x_i] == '0'
            || config->map[config->map_size - 1][x_i] == '0')
            return (-1);
        x_i++;
    }
    y_i = 1;
    while (y_i < config->map_size)
    {
        x_i = 0;
        line_end_i = config->max_line - 1;
        while (config->map[y_i][x_i] == ' ')
            x_i++;
        while (config->map[y_i][line_end_i] == ' ')
            line_end_i--;
        if (config->map[y_i][x_i] == '0' || config->map[y_i][line_end_i] == '0')
            return (-1);
        if ((y_i == (config->player.y - TILE_SIDE / 2) / TILE_SIDE
                && x_i == (config->player.x - TILE_SIDE / 2) / TILE_SIDE)
                || (y_i == (config->player.y - TILE_SIDE / 2) / TILE_SIDE
                && line_end_i == (config->player.x - TILE_SIDE / 2) / TILE_SIDE))
            return (-1);
        y_i++;
    }
    return (0);
}

int check_walls_to_close(t_map *config)
{
    int     x_i;
    int     y_i;
    char    **map;

    map = config->map;
    y_i = 0;
    if (check_borders(config) == -1)
        return (-1);
    while (y_i < config->map_size - 1)
    {
        x_i = 1;
        while (x_i < config->max_line)
        {
            if ((map[y_i][x_i] == '0') && (map[y_i - 1][x_i] == ' '
                || map[y_i + 1][x_i] == ' ' || map[y_i][x_i - 1] == ' ' 
                || map[y_i][x_i + 1] == ' '))
                return (-1);
            x_i++;
        }
        y_i++;
    }
    return (0);
}

int validation(t_map *config)
{
    if (!config || !isColors_texture_setted(config) || !config->map)
    {
        printf("params are incorrect\n");
        return (-1);
    }

    if (check_map_for_sym(config, config->map) == -1)
    {
        printf("map is incorrect\n");
        return (-1);
    }
    if (0 == (config->player.y - TILE_SIDE / 2) / TILE_SIDE
                || config->map_size - 1 == (config->player.y - TILE_SIDE / 2) / TILE_SIDE)
    {
        printf("player position on border\n");
        return (-1);
    }
    if (check_walls_to_close(config) == -1)
    {
        printf("map isn't close\n");
        return (-1);
    }
    return (0);
}
