#ifndef CONSTANTS_H
# define CONSTANTS_H

/* world */
# define PLANE_WIDTH 960
# define PLANE_HEIGHT 690
# define PLANE_CENTER PLANE_HEIGHT / 2
# define PLAYER_SPEED 0.5
# define ROTATION_SPEED 0.3
# define FOV 0.66

/* orientation */
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

/* keys */
# define KEYCODE_ESC 53
# define KEYCODE_W 13
# define KEYCODE_A 0
# define KEYCODE_S 1
# define KEYCODE_D 2
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124

/* messages */
# define MEM_ALLOC_ERR "failed to allocate memory\n"
# define INIT_WIN_ERR "failed to initialize window\n"
# define TEXTURE_ERR "failed to parse texture\n"

/* minimap */
# define MINI_MAP_WIDTH 150
# define MINI_MAP_HEIGHT 150
# define MINI_MAP_SLOTS 10
# define DRAW_MINIMAP_GRID 1

#endif
