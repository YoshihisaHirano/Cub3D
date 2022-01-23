#ifndef HOOKS_H
# define HOOKS_H
# include "../cub3D.h"

void    move_left_right(t_setup *setup, bool left);
void    dda_move_forward_backward(t_setup *setup, bool forward);
void    dda_move_left_right(t_setup *setup, bool left);
void    dda_rotate(t_setup *setup, bool left);

#endif