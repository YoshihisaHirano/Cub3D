#include "cub3D.h"

// ofc there should be some other method to check depending on map representation
bool is_wall(int x, int y, char **map) { 
    if (map[y][x] == '#') return true;
    return false;
}

bool facing_up(int angle) {
    if (angle < 180) return true;
    return false;
}

bool facing_right(int angle) {
    if (angle < 90 || angle > 270) return true;
    return false;
}

char **create_map()
{
    char **map;
    int i;

    map = malloc(sizeof(char *) * (64 * 4 + 1));
    i = 0;
    map[256] = NULL;
    while (i < 256)
    {
        map[i] = malloc(257);
        map[i][256] = '\0';
        if (i < 64 || i > 191) ft_memset(map[i], '#', 256);
        else {
            ft_memset(map[i], ' ', 256);
            ft_memset(map[i], '#', 64);
            ft_memset(map[i] + 192, '#', 64);
        }
        i++;
    }
    return map;
}

void    print_map(char **map)
{
    int i = 0;
    while (i < 256) {
        printf("%s\n", map[i]);
        i++;
    }
}

int find_int_tan(int angle)
{
    return (int)(floor(tan(angle_in_radians(angle))));
}
// A.y = Py + (Px-A.x)*tan(ALPHA);
t_point find_x_intersec(t_ppov *p) {
    int x_intersec;
    int y_intersec;
    t_point res;

    if (facing_right(p->player_angle))
        x_intersec = (bitwise_division(p->player_x, 64) << 6) + 64;
    else
        x_intersec = (bitwise_division(p->player_x, 64) << 6) - 1;
    y_intersec = p->player_y + (p->player_x - x_intersec) * find_int_tan(p->player_angle);
    res.x = x_intersec;
    res.y = y_intersec;

    return (res);
}

t_point find_y_intersec(t_ppov *p, char **map) {
    int y_intersec;
    int x_intersec;
    t_point res;

    if (facing_up(p->player_angle))
        y_intersec = (bitwise_division(p->player_y, 64) << 6) - 1;
    else
        y_intersec = (bitwise_division(p->player_y, 64) << 6) + 64;
    x_intersec = p->player_x + bitwise_division(p->player_y - y_intersec, find_int_tan(p->player_angle));
    res.y = y_intersec;
    res.x = x_intersec;

    return (res);
}

