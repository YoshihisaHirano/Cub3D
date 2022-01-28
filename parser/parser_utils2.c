#include "../cub3D.h"

void	*exit_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (NULL);
}

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
		config->texture_array[0] = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "SO", 3))
		config->texture_array[1] = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "WE", 3))
		config->texture_array[2] = ft_strdup(arr_line[1]);
	if (arr_line[1] && !ft_strncmp(*arr_line, "EA", 3))
		config->texture_array[3] = ft_strdup(arr_line[1]);
}

int handle_line(t_map *config, char *line)
{
    char **arr_line;

    arr_line = ft_split(line, ' ');
	if (!arr_line)
		return (-1);
	check_for_texture(arr_line, config);
	check_for_colors(arr_line, &(config->floor_color), "F");
	check_for_colors(arr_line, &(config->ceil_color), "C");
	free_arr(arr_line);
	free(line);
	line = NULL;
    return (0);
}

void	set_map_width(int file_fd, t_map *config)
{
	int		current_len;
	char	*line;
	int		gnl_res;

	gnl_res = 1;
	
	while (gnl_res)
	{
		gnl_res = get_next_line(file_fd, &line);
		current_len = ft_strlen(line);
		if (current_len > config->max_line)
			config->max_line = current_len;
		config->map_size++;
		free(line);
	}
}