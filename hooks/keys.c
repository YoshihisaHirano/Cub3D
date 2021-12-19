#include "hooks.h"

int key_hook(int key_code)
{
    // free the whole thing?
    if (key_code == KEYCODE_ESC)
        exit(1);
    return (0);
}