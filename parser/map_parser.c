#include "../cub3D.h"

int	set_texture_color(int file_fd, t_map *config)
{
	char	*line;
	int		i;

	i = 1;
	line = NULL;
	while (get_next_line(file_fd, &line))
	{
		i++;
		if (handle_line(config, line) == -1)
			break ;
		if (isColors_texture_setted(config))
			return (i);
	}
	if (line)
		free(line);
	if (!isColors_texture_setted(config))
	{
		printf("Error\nParams are incorrect\n");
		return (-1);
	}
	return (i);
}

int	set_map_config(int file_fd, t_map *config, char *filename)
{
	int		current_len;
	char	*line;
	int		gnl_res;
	int		lines_to_map;

	gnl_res = 1;
	lines_to_map = set_texture_color(file_fd, config);
	if (lines_to_map == -1)
		return (-1);
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
	return (0);
}

t_map	*parser(char *filename)
{
	int     file_fd;
	t_map   *config;

	if (check_filename(filename) == -1)
		return (exit_error("Error\nWrong file format"));
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (exit_error("Error\nOpen file error"));
	config = create_config();
	if (!config)
		return (NULL);
	if (set_map_config(file_fd, config, filename) == -1)
	{
		close(file_fd);
		free_config(config);
		return (NULL);
	}
	if (validation(config) == -1)
	{
		free_config(config);
		return(NULL);
	}
	show_params(config);
	return (config);
}

/* check_texture file??*/