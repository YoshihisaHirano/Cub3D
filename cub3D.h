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

typedef struct s_point {
	double	x;
	double	y;
} t_point;

typedef	struct s_player {
	t_point	pos;
	t_point	dir;
} t_player;

typedef	struct s_column
{
	bool	vertical_hit;
	int		wall_dir;
	int		wall_height;
	bool	ray_up;
	bool	ray_left;
	t_point	v_intersec;
	t_point	h_intersec;
	int		no;
} t_column;


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
	int			w;
	int			h;
}	t_img;

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

typedef struct	s_texture
{
	int		width;
	int		height;
	int		*texture;
} t_texture;

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
	t_player	*player;
	t_point		*plane;
}			t_map;

typedef struct s_setup {
	t_player		*player;
	t_map			*map;
	t_img			*image;
	t_win			*win;
	t_column		*col;
	t_texture		texture[4];
	t_point			*plane;
} t_setup;

typedef struct  s_raycaster {
    t_point deltas;
    t_point step;
    t_point ray_dir;
    t_point on_map;
    t_point side_dist;
    double  wall_dist;
    int     wall_height;
} t_raycaster;

typedef struct s_minimap
{
	t_img		img;
	t_rectangle	rec;
	int			player_x;
	int			player_y;
	int			map_start_x;
	int			map_start_y;
	int			inner_map_size;
}				t_minimap;

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
void		set_map_width(int file_fd, t_map *config);
int			fill_map_config(t_map *config, int lines_to_map, int file_fd);
int			validation(t_map *config);
int			check_top_bottom_borders(t_map *config);
int			setup_player(t_map *config, char char_for_check, int x_i, int y_i);
int			is_player_setted(t_map *config);
int			check_filename(char *file_name);
void		*exit_error(char *msg);
int			handle_line(t_map *config, char *line);
void		draw_minimap(t_setup *setup);
void		draw_rectangle2(t_img *img, t_rectangle *params, int color);
void		set_img_rec(t_setup *setup, t_minimap *minimap);
void		get_inner_map_size(t_setup *setup, t_minimap *minimap);
void		get_player_position(t_setup *setup, t_minimap *minimap);
void		set_map_start(t_setup *setup, t_minimap *minimap);
int			check_wall(t_map *config, int x, int y);
void			my_pix_put(t_img *img, int x, int y, int color);
void			find_wall_dir(t_column *col, t_point *ray_dir);
void			clear_setup(t_setup *setup);
int				create_trgb(int t, int r, int g, int b);
void			draw_rectangle(t_img *img, t_rectangle *params, int color);
void			draw_plane(t_setup *setup);
void			error_exit(char *message);
t_setup			*init_all();
int				key_hook(int key_code, t_setup *setup);
void			load_textures(t_setup *setup);
void			render_tex_column(t_setup *setup, int wall_top, int wall_bottom);
void			render(t_setup *setup);
int				get_color(t_setup *setup, int x, int y);
void			draw_column(t_setup *setup, t_raycaster *r, int wall_top, int tex_x);
int				get_texture_x(t_setup *setup, t_raycaster *r);
int				exit_procedure(t_setup *setup);

#endif
