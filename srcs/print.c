#include "../inc/ft_ls.h"

void    print_with_width(const char *str, int width)
{
    int spaces;

    spaces = width - ft_strlen(str);
    ft_putstr(str);
    if (spaces > 0)
        while(spaces--)
            write(1, " ", 1);
}