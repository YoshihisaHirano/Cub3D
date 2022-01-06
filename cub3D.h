#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "hooks/hooks.h"
# include "utils/utils.h"


# define HEIGHT 200 //projection plane height
# define WIDTH 320 // projection plane width, therefore 320 columns in total
# define EV_DESTR_NOTIFY 17
# define MASK_NO_EVENT 0L

# define PLAYER_HEIGHT 32 // player's height is half the wall's height
# define PLAYER_FOV 60 // player's field of view
# define WALL_SIDE 64 // the world consists of 64x64 cubes
# define DISTANCE_TO_PLANE 277 // half_of_width / tan(FOV / 2)
# define RAY_ANGLE_STEP 0.1875 // columns_qty / FOV; angle between subsequent rays
# define MAP_BORDER 256

/*
map, # - wall, 256 x 256 units
####
#  #
#  #
####

degrees schema:
	   270
		|
		|
180------------0
		|
		|
		90

the plane starts at 0,0 at the to left corner
0__________x
|
|
|
y
*/

typedef struct s_point {
	int	x;
	int	y;
} t_point;

typedef struct s_ppov {
	int player_x; // on the map
	int player_y; // on the map
	int player_angle; // in degrees, with regards to X-axis
} t_ppov;


typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
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

typedef struct s_map
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_color	*floor;
	t_color	*ceil;
	char	**map;
	int		player_look;
	int		map_size;
	int		max_line;
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
int			skip_to_map(int file_fd, int lines_to_map);
int			fill_map_config(t_map *config, int lines_to_map, int file_fd);
int			validation(t_map *config);	
int			check_filename(char *file_name);
void		*exit_error(char *msg);
int			check_wall(t_map *config, int x, int y);


#endif
