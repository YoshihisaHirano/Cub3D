#include "../cub3D.h"

void	free_arr(char **arr)
{
	char	**arr_tmp;

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

void	free_config(t_map *config)
{
	if (!config)
		return ;
	if (config->texture_array)
		free_arr(config->texture_array);
	free_arr(config->map);
	if (config->plane)
		free(config->plane);
	if (config->player)
		free(config->player);
	free(config);
}

void	clear_setup(t_setup *setup)
{
	int	i;

	i = 0;
	if (setup->map)
		free_config(setup->map);
	if (setup->win)
		free(setup->win);
	if (setup->image)
		free(setup->image);
	while (i < 4)
	{
		free(setup->texture[i].texture);
		i++;
	}
	free(setup);
}
