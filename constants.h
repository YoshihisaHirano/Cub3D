#ifndef CONSTANTS_H
# define CONSTANTS_H
/* world */
# define TILE_SIDE 64//320
# define PLANE_WIDTH 320//1600//320//
# define PLANE_HEIGHT 200//1000//200//
# define PLANE_CENTER (PLANE_HEIGHT / 2)
# define PLAYER_PLANE_DST 277//1386//277// (half plane width / tan(30 deg))

/* angles */
# define ANGLE60 PLANE_WIDTH
# define ANGLE30 (ANGLE60 / 2)
# define ANGLE90 (ANGLE30 * 3)
# define ANGLE180 (ANGLE90 * 2)
# define ANGLE270 (ANGLE90 * 3)
# define ANGLE360 (ANGLE60 * 6)
# define ANGLE0 0
# define ANGLE5 (ANGLE30 / 5)
# define ANGLE10 (ANGLE5 * 2)

/* player's attributes */
# define PLAYER_SPEED 16//80
# define PLAYER_X 136
# define PLAYER_Y 136
# define PLAYER_ANGLE ANGLE0
# define PLAYER_HEIGHT (TILE_SIDE / 2)
# define MAP_WIDTH 12
# define MAP_HEIGHT 12

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

#endif
