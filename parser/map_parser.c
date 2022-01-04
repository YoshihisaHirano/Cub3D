#include "../cub3D.h"

void    free_arr(char **arr)
{
    char **arr_tmp;

    if (!arr && !(*arr))
        return ;
    arr_tmp = arr;
    while (*arr_tmp)
    {
        free(*arr_tmp);
        arr_tmp++;
    }
    free(arr);
}

void    check_for_texture(char **arr_line, t_map *config)
{
    if (!arr_line && !(*arr_line))
        return ;
    if (!ft_strncmp(*arr_line, "NO", 3))
        config->NO = ft_strdup(arr_line[1]);
}


int parser(char *filename)
{
    int     file_fd;
    char    *line;
    char    **arr_line;
    t_map   *config;

    config = malloc(sizeof(t_map));
    if (!config)
        return (-1);
    file_fd = open(filename, O_RDONLY);
    if (file_fd == -1)
    {
        printf("open file error\n");
        return (-1);
    }

    while (get_next_line(file_fd, &line))
    {
        arr_line = ft_split(line, ' ');
        check_for_texture(arr_line, config);
        printf("|%s|\n", *arr_line);
        free_arr(arr_line);
        free(line);
    }
    free(line);
    close(file_fd);
    show_params(config);
    free(config);
    return (0);
}