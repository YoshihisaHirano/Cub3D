#include "../cub3D.h"

// empty lines at the end of file??? is it ok?? 

int check_filename(char *file_name)
{
    int len;

    len = ft_strlen(file_name);
    if (ft_strncmp(file_name + len - 4, ".cub", 5))
        return (-1);
    else
        return (0);
}

int check_map_chars(t_map *config, char **map)
{
    int     not_empty_line;
    int     y_i;
    int     x_i;

    y_i = 0;
    while (map[y_i])
    {
        x_i = 0;
        not_empty_line = 0;
        while (map[y_i][x_i])
        {
            if (!ft_strchr("NSEW01 ", map[y_i][x_i]))
                return (-1);
            if (ft_strchr("NSEW", map[y_i][x_i]))
                if (setup_player(config, map[y_i][x_i], x_i, y_i) == -1)
                    return (-1);
            if (not_empty_line || ft_strchr("01NSEW", map[y_i][x_i])) // for not empty lines
                    not_empty_line = 1;
            x_i++;
        }
        if (!not_empty_line)
            return (-1);
        y_i++;
    }
    return (0);
}

int check_borders(t_map *conf)
{
    int     x_i;
    int     y_i;
    int     line_end_i;

    if (check_top_bottom_borders(conf) == -1)
        return (-1);
    y_i = 1;
    while (y_i < conf->map_size)
    {
        x_i = 0;
        line_end_i = conf->max_line - 1;
        while (conf->map[y_i][x_i] == ' ')
            x_i++;
        while (conf->map[y_i][line_end_i] == ' ')
            line_end_i--;
        if (conf->map[y_i][x_i] == '0' || conf->map[y_i][line_end_i] == '0')
            return (-1);
        if ((y_i == conf->player->pos.y - 0.5
                && x_i == conf->player->pos.x - 0.5)
                || (y_i == conf->player->pos.y - 0.5
                && line_end_i == conf->player->pos.x - 0.5))
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
    y_i = 1;
    if (check_borders(config) == -1)
        return (-1);
    while (y_i < config->map_size - 1)
    {
        x_i = 1;
        while (x_i < config->max_line)
        {
            if ((map[y_i][x_i] == '0')
                && (map[y_i - 1][x_i] == ' '
                || map[y_i + 1][x_i] == ' '
                || map[y_i][x_i - 1] == ' ' 
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
        printf("Error\nParams are incorrect\n");
        return (-1);
    }
    if (check_map_chars(config, config->map) == -1)
    {
        printf("Error\nMap is incorrect\n");
        return (-1);
    }
    if (is_player_setted(config) == -1)
        return (-1);
    if (check_walls_to_close(config) == -1)
    {
        printf("Error\nMap isn't close\n");
        return (-1);
    }
    return (0);
}