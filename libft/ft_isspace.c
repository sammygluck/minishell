#include "libft.h"

int ft_isspace(char *chr)
{
    if ((chr == 32) || (chr <= 13 && chr >= 9))
        return (1);
    else
        return (0);
}