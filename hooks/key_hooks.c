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
        turn(setup, true);
    if (key_code == KEYCODE_RIGHT)
        turn(setup, false);
    if (key_code == KEYCODE_W)
        move_forwards_backwards(setup, true);
    if (key_code == KEYCODE_S)
        move_forwards_backwards(setup, false);
    return (0);
}