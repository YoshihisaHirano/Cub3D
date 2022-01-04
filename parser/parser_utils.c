#include "../cub3D.h"

void show_params(t_map *config)
{
    printf("\n-----config------\n");
    if (config->NO)
        printf("NO: %s\n", config->NO);
    if (config->SO)
        printf("SO: %s\n", config->SO);    
    if (config->WE)
        printf("WE: %s\n", config->WE);
    if (config->EA)
        printf("EA: %s\n", config->EA);
    printf("color setup: \n");
    printf("Ceil : ");
        printf("%i ", config->ceil->R);
        printf("%i ", config->ceil->G);
        printf("%i ", config->ceil->B);
    printf("\n");
    printf("Floor : ");
        printf("%i ", config->floor->R);
        printf("%i ", config->floor->G);
        printf("%i ", config->floor->B);
    printf("\n");
}

t_map   *create_config(void)
{
    t_map   *config;

    config = malloc(sizeof(t_map));
    if (!config)
        return (NULL);
    config->ceil = malloc(sizeof(t_color));
    if (!config->ceil)
        return (NULL);
    config->floor = malloc(sizeof(t_color));
    if (!config->floor)
        return (NULL);
    config->NO = NULL;
    config->SO = NULL;
    config->WE = NULL;
    config->EA = NULL;
    config->floor->R = 0;
    config->floor->G = 0;
    config->floor->B = 0;
    config->ceil->R = 0;
    config->ceil->G = 0;
    config->ceil->B = 0;
    config->map = NULL;
    return (config);
}

void    free_config(t_map *config)
{
    if (!config)
        return ;
    if (config->NO)
       free(config->NO);
    if (config->SO)
        free(config->SO);    
    if (config->WE)
        free(config->WE);
    if (config->EA)
        free(config->EA);
    if (config->ceil)
        free(config->ceil);
    if (config->floor)
        free(config->floor);
    free(config);
}

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