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
	for (int j = 0; config->map[j]; j++)
		printf("|%s|\n", config->map[j]);
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
	config->floor->R = -1;
	config->floor->G = -1;
	config->floor->B = -1;
	config->ceil->R = -1;
	config->ceil->G = -1;
	config->ceil->B = -1;
	config->map = NULL;
	config->player_look = 0;
	return (config);
}

int isColors_texture_setted(t_map *config)
{
	if (!config->NO)
	   return (0);
	if (!config->SO)
		return (0);
	if (!config->WE)
		return (0);
	if (!config->EA)
		return (0);
	if (config->ceil->R == -1 || config->ceil->G == -1
			|| config->ceil->B == -1)
		return (0);
	if (config->floor->R == -1 || config->floor->G == -1
			|| config->floor->B == -1)
		return (0);
	return (1);
}

int	skip_to_map(int file_fd, int lines_to_map)
{
	char	*line;
	char	*tmp_str;
	while (get_next_line(file_fd, &line))
	{
		tmp_str = ft_strtrim(line, " ");
		if (*tmp_str)
		{
			free(tmp_str);
			free(line);
			break ;
		}
		lines_to_map++;
		free(line);
		free(tmp_str);
	}
	return (lines_to_map);
}


int fill_map_config(t_map *config, int lines_to_map, int map_size, int file_fd)
{
	int		i;
	char	*line;
	int		gnl_res;

	config->map = malloc((map_size + 1) * sizeof(char *));
	if (config->map == NULL)
		return (-1);
	gnl_res = 1;
	i = 1;
	while (i < lines_to_map)
	{
		get_next_line(file_fd, &line);
		free(line);
		i++;
	}
	i = 0;
	while (gnl_res)
	{
		gnl_res = get_next_line(file_fd, &(config->map[i]));
		i++;
	}
	config->map[map_size] = NULL;
	return (0);
}

int	exit_error(char *msg)
{
	printf("%s\n", msg);
	return (-1);
}