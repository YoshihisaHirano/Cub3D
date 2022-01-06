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
    int     i;
    int     k;

    i = 0;
    while (map[i])
    {
        k = 0;
        has_map_char = 0;
        while (map[i][k])
        {
            if (map[i][k] == 'N' || map[i][k] == 'S' || map[i][k] == 'E' || map[i][k] == 'W')
                if (config->player_look != -1)
                    return (-1);
                else
                {
                    if (map[i][k] == 'N')
                        config->player_look = 270;
                    if (map[i][k] == 'S')
                        config->player_look = 90;
                    if (map[i][k] == 'E')
                        config->player_look = 0;
                    if (map[i][k] == 'W')
                        config->player_look = 180;
                }
            else if (map[i][k] != '0' && map[i][k] != '1' && map[i][k]  != ' ')
                    return (-1);
            if (has_map_char || map[i][k] == '0' || map[i][k] == '1' || map[i][k] == 'N'
                || map[i][k] == 'S' || map[i][k] == 'E' || map[i][k] == 'W')
                    has_map_char = 1;
            k++;
        }
        if (!has_map_char)
            return (-1);
        i++;
    }
    return (0);
}

// check is fist line 1
// check is last line 1
// check 1st and last sym in line is 1
// check is every sym except 

// int check_walls_to_close(t_map *config)
// {

// }

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
    return (0);
}