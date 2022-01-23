#include "hooks.h"

void	exit_procedure(t_setup *setup)
{
    clear_setup(setup);
    exit(0);
}

int key_hook(int key_code, t_setup *setup)
{
    if (key_code == KEYCODE_ESC)
        exit_procedure(setup);
    if (key_code == KEYCODE_LEFT)
        dda_rotate(setup, true);
    if (key_code == KEYCODE_RIGHT)
        dda_rotate(setup, false);
    if (key_code == KEYCODE_W)
        dda_move_forward_backward(setup, true);
    if (key_code == KEYCODE_S)
        dda_move_forward_backward(setup, false);
    if (key_code == KEYCODE_A)
        dda_move_left_right(setup, true);
    if (key_code == KEYCODE_D)
        dda_move_left_right(setup, false);
    return (0);
}