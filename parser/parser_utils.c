#include "../cub3D.h"

void show_params(t_map *config)
{
	printf("\n-----config------\n");
	printf("%p\n", config);
	if (config->NO)
		printf("NO: %s = %p\n", config->NO, config->NO);
	if (config->SO)
		printf("SO: %s = %p\n", config->SO, config->SO);    
	if (config->WE)
		printf("WE: %s = %p\n", config->WE, config->WE);
	if (config->EA)
		printf("EA: %s = %p\n", config->EA, config->EA);
	printf("color setup: \n");
	printf("Ceil : ");
		printf("%i ", config->ceil_color);
	printf("\n");
	printf("Floor : ");
		printf("%i ", config->floor_color);
	printf("\n");
	printf("map %p\n", config->map);
	for (int j = 0; config->map[j]; j++)
		printf("|%s|\n", config->map[j]);
}

t_map   *create_config(void)
{
	t_map   *config;

	config = malloc(sizeof(t_map));
	if (!config)
		return (NULL);
	config->NO = NULL;
	config->SO = NULL;
	config->WE = NULL;
	config->EA = NULL;
	config->player.angle = -1;
	config->player.x = -1;
	config->player.y = -1;
	config->ceil_color = -1;
	config->floor_color = -1; 
	config->map = NULL;
	config->map_size = 1;
	config->max_line = 0;
	return (config);
}

int isColors_texture_setted(t_map *config)
{
	if (!config)
		return (0);
	if (!config->NO)
	   return (0);
	if (!config->SO)
		return (0);
	if (!config->WE)
		return (0);
	if (!config->EA)
		return (0);
	if (config->ceil_color == -1)
		return (0);
	if (config->floor_color == -1)
		return (0);
	return (1);
}

int	skip_to_map(t_map *config, int file_fd, int lines_to_map)
{
	char	*line;
	char	*tmp_str;

	while (get_next_line(file_fd, &line))
	{
		tmp_str = ft_strtrim(line, " ");
		if (*tmp_str)
		{
			config->max_line = ft_strlen(line);
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

void	add_spaces(t_map *config, int i)
{
	char	*tmp;
	int		len;

	len = ft_strlen(config->map[i]);
	if (len < config->max_line)
	{
		tmp = config->map[i];
		config->map[i] = ft_calloc((config->max_line + 1), sizeof(char));
		ft_memset(config->map[i], ' ', config->max_line);
		ft_memcpy(config->map[i], tmp, len);
		free(tmp);
	}
}

int fill_map_config(t_map *config, int lines_to_map, int file_fd)
{
	int		i;
	char	*line;
	int		gnl_res;

	config->map = malloc((config->map_size + 1) * sizeof(char *));
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
		add_spaces(config, i);
		i++;
	}
	config->map[config->map_size] = NULL;
	return (0);
}