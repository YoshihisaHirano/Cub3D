#ifndef CONSTANTS_H
# define CONSTANTS_H
/* world */
# define TILE_SIDE 320
# define PLANE_WIDTH 1600
# define PLANE_HEIGHT 1000
# define PLANE_CENTER (PLANE_HEIGHT / 2)
# define PLAYER_PLANE_DST 1386 // (half plane width / tan(30 deg))

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
# define PLAYER_X 100
# define PLAYER_Y 160
# define PLAYER_ANGLE ANGLE0
# define PLAYER_HEIGHT (TILE_SIDE / 2)
# define MAP_WIDTH 12
# define MAP_HEIGHT 12

/* keys */
# define KEYCODE_ESC 53

#endif
