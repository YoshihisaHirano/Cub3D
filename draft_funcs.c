#include "cub3D.h"

void	draw_column(t_img *img, int x, int y, int height);

// temporary map funcs
char **create_map()
{
    char **map;
    int i;

    map = malloc(sizeof(char *) * (MAP_BORDER + 1));
    i = 0;
    map[MAP_BORDER] = NULL;
    while (i < MAP_BORDER)
    {
        map[i] = malloc(MAP_BORDER + 1);
        map[i][MAP_BORDER] = '\0';
        if (i < WALL_SIDE || i > 191) ft_memset(map[i], '#', MAP_BORDER);
        else {
            ft_memset(map[i], ' ', MAP_BORDER);
            ft_memset(map[i], '#', WALL_SIDE);
            ft_memset(map[i] + 192, '#', WALL_SIDE);
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
// ofc there should be some other method to check if a wall has been hit depending on map representation
bool is_wall(t_point *point, char **map)
{ 
    if (map[point->y][point->x] == '#') return true;
    return false;
}

bool facing_up(int angle)
{
    if (angle < 180) return true;
    return false;
}

bool facing_right(int angle)
{
    if (angle < 90 || angle > 270) return true;
    return false;
}

bool on_the_border(t_point *point)
{
    if (point->y == 0 || point->x == 0 || point->y == MAP_BORDER || point->x == MAP_BORDER)
        return true;
    return false;
}

double find_trigonom(double angle, double (*f)(double))
{
    return (floor(f(angle_in_radians(angle))));
}

void    normalize_point(t_point *point)
{
    if (point->x < 0)
        point->x = 0;
    if (point->y < 0)
        point->y = 0;
    if (point->x > MAP_BORDER)
        point->x = MAP_BORDER;
    if (point->y > MAP_BORDER)
        point->y = MAP_BORDER;
}

t_point find_first_x_intersec(t_ppov *p, double angle)
{
    int y_intersec;
    int x_intersec;
    t_point res;

    if (facing_up(angle))
        y_intersec = (divide_nums((double)p->player_y, (double)WALL_SIDE) << 6) - 1;
    else
        y_intersec = (divide_nums((double)p->player_y, (double)WALL_SIDE) << 6) + WALL_SIDE;
    x_intersec = p->player_x + divide_nums((double)(p->player_y - y_intersec), find_trigonom(angle, tan));
    res.y = y_intersec;
    res.x = x_intersec;
    return (res);
}

t_point find_first_y_intersec(t_ppov *p, double angle)
{
    int x_intersec;
    int y_intersec;
    t_point res;

    if (facing_right(angle))
        x_intersec = (divide_nums((double)p->player_x, (double)WALL_SIDE) << 6) + WALL_SIDE;
    else
        x_intersec = (divide_nums((double)p->player_x, (double)WALL_SIDE) << 6) - 1;
    y_intersec = p->player_y + (p->player_x - x_intersec) * (int)(find_trigonom(angle, tan));
    res.x = x_intersec;
    res.y = y_intersec;
    return (res);
}

t_point find_y_intersec(t_ppov *p, char **map, double angle)
{
    int delta_x;
    int delta_y;
    t_point res;

    res = find_first_y_intersec(p, angle);
    normalize_point(&res);
    if (is_wall(&res, map))
        return (res);
    delta_x = WALL_SIDE;
    if (! facing_right(angle))
        delta_x = -WALL_SIDE;
    delta_y = WALL_SIDE * (int)find_trigonom(angle, tan);
    while (! is_wall(&res, map) || ! on_the_border(&res))
    {
        res.x += delta_x;
        res.y += delta_y;
        normalize_point(&res);
    }
    return (res);
}

t_point find_x_intersec(t_ppov *p, char **map, double angle)
{
    int delta_x;
    int delta_y;
    t_point res;

    res = find_first_x_intersec(p, angle);
    normalize_point(&res);
    if (is_wall(&res, map))
        return (res);
    delta_y = WALL_SIDE;
    if (facing_up(angle))
        delta_y = -WALL_SIDE;
    delta_x = divide_nums((double)WALL_SIDE, find_trigonom(angle, tan));
    while (! is_wall(&res, map) || ! on_the_border(&res))
    {
        res.x += delta_x;
        res.y += delta_y;
        normalize_point(&res);
    }
    return (res);
}

int find_smallest_dist(t_ppov *p, char **map, double angle)
{
    t_point y_intersec;
    t_point x_intersec;
    int first_dst;
    int second_dst;

    y_intersec = find_y_intersec(p, map, angle);
    x_intersec = find_x_intersec(p, map, angle);
    printf("%d x_inter.x, %d y_inter.x\n", x_intersec.x, y_intersec.x);
    first_dst = divide_nums((double)(abs(p->player_x - x_intersec.x)), find_trigonom(angle, cos));
    second_dst = divide_nums((double)(abs(p->player_x - y_intersec.x)), find_trigonom(angle, cos));
    if (second_dst < first_dst)
        return (second_dst);
    return (first_dst);
}

int correct_dst(int distorted_dst, double relative_angle)
{
    return (distorted_dst * (int)(find_trigonom(relative_angle, cos)));
}

void    draw_plane(t_ppov *p, char **map, t_img *img)
{
    double relative_angle; // angle of the ray that is being cast relative to the viewing angle
    double current_angle;
    int dst;
    int proj_height;
    int proj_start_y;
    int i;

    current_angle = p->player_angle - divide_nums((double)PLAYER_FOV, 2.0);
    relative_angle = -30; //for removing fish eye distortion, !!! check where this value is coming from
    i = 0;
    while (i < WIDTH)
    {
        dst = find_smallest_dist(p, map, current_angle);
        // dst = correct_dst(dst, relative_angle);
        printf("%f - relative_angle\n", relative_angle);
        // printf("%d - dst, %d - bitwise division 200/2\n", dst, divide_nums((double)HEIGHT, 2.0));
        proj_height = divide_nums((double)WALL_SIDE, dst) * DISTANCE_TO_PLANE;
        proj_start_y = divide_nums((double)HEIGHT, 2.0) - divide_nums((double)proj_height, 2.0);
        printf("%d - height, %d -y\n", proj_height, proj_start_y);
        draw_column(img, i, proj_start_y, proj_height);
        current_angle += RAY_ANGLE_STEP;
        relative_angle += RAY_ANGLE_STEP;
        i++;
    }
}