#include "../cub3D.h"

int check_for_colors(char **arr_line, t_color *color_el, char *color_place)
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
		color_el->R = ft_atoi(tmp_arr[0]);
		color_el->G = ft_atoi(tmp_arr[1]);
		color_el->B = ft_atoi(tmp_arr[2]);
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

void	set_texture_color(int file_fd, t_map *config)
{
	char	*line;
	char	**arr_line;

	while (get_next_line(file_fd, &line))
	{
		arr_line = ft_split(line, ' ');
		check_for_texture(arr_line, config);
		check_for_colors(arr_line, config->floor, "F");
		check_for_colors(arr_line, config->ceil, "C");
		free_arr(arr_line);
		free(line);
	}
	free(line);
}

void	set_map(int file_fd, t_map *config)
{
	// one str?? 
	// linked list
	// when quit from 1st gnl
	char	*line;
	(void) config;
	while (get_next_line(file_fd, &line))
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
}

int parser(char *filename)
{
	int     file_fd;
	t_map   *config;

	config = create_config();
	if (!config)
		return (-1);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		printf("open file error\n");
		return (-1);
	}
	set_texture_color(file_fd, config);
	set_map(file_fd, config);
	close(file_fd);
	show_params(config);
	free_config(config);
	return (0);
}