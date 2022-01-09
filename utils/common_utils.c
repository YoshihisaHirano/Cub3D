#include "../cub3D.h"

void    error_exit(char *message)
{
    write(2, message, ft_strlen(message));
    exit(1);
}