#include "../cub3D.h"

void show_params(t_map *config)
{
    printf("-----config------\n");
    if (config->NO)
        printf("NO: %s\n", config->NO);
    if (config->SO)
        printf("SO: %s\n", config->SO);    
    if (config->WE)
        printf("WE: %s\n", config->WE);
    if (config->EA)
        printf("EA: %s\n", config->EA);
    printf("color setup: \n");
    if (config->F_R)
        printf("%i ", config->F_R);
    if (config->F_G)
        printf("%i ", config->F_G);
    if (config->F_B)
        printf("%i ", config->F_B);
    if (config->C_R)
        printf("%i ", config->C_R);
    if (config->C_G)
        printf("%i ", config->C_G);
    if (config->C_B)
        printf("%i ", config->C_B);
}

void    init_config(t_map *config)
{
    config->NO = NULL;
    config->SO = NULL;
    config->WE = NULL;
    config->EA = NULL;
    config->F_R = 0;
    config->F_G = 0;
    config->F_B = 0;
    config->C_R = 0;
    config->C_G = 0;
    config->C_B = 0;
    config->map = NULL;

}