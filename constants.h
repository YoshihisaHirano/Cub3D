#ifndef CONSTANTS_H
# define CONSTANTS_H

/* world */
// # define TILE_SIDE 320//
// # define PLANE_WIDTH 1600//
// # define PLANE_HEIGHT 1000//
// # define PLANE_CENTER (PLANE_HEIGHT / 2)
// # define PLAYER_PLANE_DST 1386// (half plane width / tan(30 deg))

# define TILE_SIDE 64//320//
# define PLANE_WIDTH 960//1600//
# define PLANE_HEIGHT 690//1000//
# define PLANE_CENTER (PLANE_HEIGHT / 2)
# define PLAYER_PLANE_DST 277//1386// (half plane width / tan(30 deg))

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
// # define PLAYER_SPEED 80//
// # define PLAYER_X 1600// //delete
// # define PLAYER_Y 1600// //delete
# define PLAYER_ANGLE ANGLE270 //delete
# define PLAYER_HEIGHT (TILE_SIDE / 2) //delete ??
# define PLAYER_SPEED 0.5//80//
# define ROTATION_SPEED 0.3
# define PLAYER_X 320//1600// //delete
# define PLAYER_Y 320//1600// //delete

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

#endif
