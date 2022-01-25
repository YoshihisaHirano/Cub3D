#include "../cub3D.h"

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
	free_arr(config->map);
	if (config->plane)
		free(config->plane);
	if (config->player)
		free(config->player);
	free(config);
}

void    free_arr(char **arr)
{
	char **arr_tmp;

	if (!arr)
		return ;
	arr_tmp = arr;
	while (*arr_tmp)
	{
		free(*arr_tmp);
		arr_tmp++;
	}
	free(arr);
}