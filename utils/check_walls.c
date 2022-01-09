#include "../cub3D.h"

int check_wall(t_map *config, int x, int y)
{
    if (y >= config->map_size)
    {
        printf("out of map (y)\n");
        return (0);
    }
    if (x >= (int) ft_strlen(config->map[y]))
    {
        printf("out of line\n");
        return (0);
    }
    // printf(" %d %lu\n%s\n", x, ft_strlen(config->map[y]), config->map[y]);

    if (config->map[y][x] == '1')
        return (1);
    if (config->map[y][x] == '0')
        return (0);
    // if (config->map[y][x] == 'N' || config->map[y][x] == 'S'
    //     || config->map[y][x] == 'E' || config->map[y][x] == 'W')
        // printf("its a player wtf??? \n");
    return (0);
}