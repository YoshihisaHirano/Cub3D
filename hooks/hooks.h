#ifndef HOOKS_H
# define HOOKS_H
# include "../cub3D.h"

void    turn(t_setup *setup, bool left);
void	move_forwards_backwards(t_setup *setup, bool forwards);
void    move_left_right(t_setup *setup, bool left);

#endif