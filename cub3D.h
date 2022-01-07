#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "constants.h"

typedef struct s_trig_tables {
	double	sin[ANGLE360 + 1];
	double	inv_sin[ANGLE360 + 1];
	double	cos[ANGLE360 + 1];
	double	inv_cos[ANGLE360 + 1];
	double	tan[ANGLE360 + 1];
	double	inv_tan[ANGLE360 + 1];
	double	fish_table[ANGLE60 + 1];
	double	x_step_table[ANGLE360 + 1];
	double	y_step_table[ANGLE360 + 1];
}	t_trig_tables;

typedef	struct s_player {
	int	x;
	int	y;
	int	angle;
} t_player;

typedef struct s_point {
	double	x;
	double	y;
} t_point;

typedef struct s_rectangle {
	int x;
	int y;
	int height;
	int	width;
} t_rectangle;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_config {
	t_player		*player;
	t_trig_tables	*tables;
	char 			*map;
	t_img			*image;
	int				scale;
} t_config;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
	t_img	*image;
}	t_win;

typedef struct s_color
{
	int	R;
	int	G;
	int	B;
}		t_color;

typedef struct s_map
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			floor_color;
	int			ceil_color;
	char		**map;
	int			map_size;
	int			max_line;
	t_player	player;
}			t_map;


// parser part
void show_params(t_map *config); // to delete
/* gnl */
typedef struct s_set_fd
{
	char	*str;
	int		fd;
	void	*next;
	int		read_res;
}			t_set_fd;

char		*ft_strdup_gnl(char *src, int len, int offset);
char		*ft_strjoin_gnl(char *s1, char *s2, int len);
int			ft_strlen_gnl(const char *s);
t_set_fd	*get_current_el(t_set_fd **list, int fd);
int			get_next_line(int fd, char **line);
void		lst_free(t_set_fd **list);
t_map		*parser(char *filename);
t_map	    *create_config(void);
void		free_arr(char **arr);
void    	free_config(t_map *config);
int			isColors_texture_setted(t_map *config);
int			skip_to_map(t_map *config, int file_fd, int lines_to_map);
int			fill_map_config(t_map *config, int lines_to_map, int file_fd);
int			validation(t_map *config);
int			setup_player(t_map *config, char char_for_check, int x_i, int y_i);
int			is_player_setted(t_map *config);
int			check_filename(char *file_name);
void		*exit_error(char *msg);
int			check_wall(t_map *config, int x, int y);
void			draw_column(t_img *img, t_point coords, int height, int color);
t_trig_tables	*create_trig_tables(void);
void			add_fish_table(t_trig_tables *tables);
void			add_step_tables(t_trig_tables *tables);
double			angle_to_radians(int angle);
bool			facing_down(int angle);
bool			facing_left(int angle);
int				get_start_angle(int player_angle);
double			dst_to_horizontal(t_trig_tables *tables, t_player *player,
									char *map, int curr_angle);
double			dst_to_vertical(t_trig_tables *tables, t_player *player,
								  char *map, int curr_angle);
t_config		*create_main_config();
void			init_win(t_win *win);
void			init_img(t_img *img, t_win *win);
int				create_trgb(int t, int r, int g, int b);
void			draw_rectangle(t_img *img, t_rectangle *params, int color);
void			draw_plane(t_config *conf);

#endif
