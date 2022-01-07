#include "../cub3D.h"

int check_for_colors(char **arr_line, int *color_el, char *color_place)
{
	char **tmp_arr;
	if (!arr_line || !(*arr_line) || !(**arr_line))
		return (0);
	if (arr_line[1] && !ft_strncmp(*arr_line, color_place, 2))
	{
		tmp_arr = ft_split(arr_line[1], ',');
		if (!tmp_arr)
			return (0);
		if (!tmp_arr[0] || !tmp_arr[1] || !tmp_arr[2])
			return (0);
		*color_el = create_trgb(0, ft_atoi(tmp_arr[0]), ft_atoi(tmp_arr[1]),
				ft_atoi(tmp_arr[2]));
		free_arr(tmp_arr);
	}
	return (0);
}

void    check_for_texture(char **arr_line, t_map *config)
{
	if (!arr_line || !(*arr_line) || !(**arr_line))
		return ;
	if (arr_line[1] && !ft_strncmp(*arr_line, "NO", 3))
		config->NO = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "SO", 3))
		config->SO = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "WE", 3))
		config->WE = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "EA", 3))
		config->EA = ft_strdup(arr_line[1]);
}

int	set_texture_color(int file_fd, t_map *config)
{
	char	*line;
	char	**arr_line;
	int		i;

	i = 1;
	while (get_next_line(file_fd, &line))
	{
		i++;
		arr_line = ft_split(line, ' ');
		check_for_texture(arr_line, config);
		check_for_colors(arr_line, &(config->floor_color), "F");
		check_for_colors(arr_line, &(config->ceil_color), "C");
		free_arr(arr_line);
		free(line);
		line = NULL;
		if (isColors_texture_setted(config))
			return (i);
	}
	if (line)
		free(line);
	if (!isColors_texture_setted(config))
		return (-1);
	return (i);
}

int	set_map(int file_fd, int lines_to_map, t_map *config, char *filename)
{
	int		current_len;
	char	*line;
	int		gnl_res;

	gnl_res = 1;
	lines_to_map = skip_to_map(config, file_fd, lines_to_map);
	while (gnl_res)
	{
		gnl_res = get_next_line(file_fd, &line);
		current_len = ft_strlen(line);
		if (current_len > config->max_line)
			config->max_line = current_len;
		config->map_size++;
		free(line);
	}
	close(file_fd);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (-1);
	if (fill_map_config(config, lines_to_map, file_fd) == -1)
		return (-1);
	close(file_fd);
	printf("map size: %d\n lines_to_map %d\n max_len %d\n",
			config->map_size, lines_to_map, config->max_line);
	return (0);
}

t_map	*parser(char *filename)
{
	int     file_fd;
	t_map   *config;
	int		lines_to_map;

	if (check_filename(filename) == -1)
		return (exit_error("---Wrong file format"));
	config = create_config();
	if (!config)
		return (NULL);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (exit_error("Open file error"));
	lines_to_map = set_texture_color(file_fd, config);
	if (lines_to_map == -1)
	{
		free_config(config);
		return (exit_error("---Map error"));
	}
	if (set_map(file_fd, lines_to_map, config, filename) == -1)
	{
		free_config(config);
		return (NULL);
	}
	if (validation(config) == -1)
		return(exit_error("---validation error"));
	show_params(config);
	return (config);
}