#include "main.h"

color_t color_guard(char *color, int line)
{
    char    **color_idents;
    int     color_value;
    int     i;
    color_t color_return;

    color_idents = ft_split(color, ",");
    i = 0;
    ft_bzero(&color_return, sizeof(color_t));
    while (color_idents[i])
    {
        if (i > 2)
            throw_error("Unrespected RGB syntax at line: ", line, color);
        color_value = ft_atoi(color_idents[i]);
        if (color_value > 255 || color_value < 0)
            throw_error("Invalid color value [0, 255] in line: ", line, color_idents[i]);
        if (i == 0)
            color_return.r = color_value;
        if (i == 1)
            color_return.g = color_value;
        if (i == 2)
            color_return.b = color_value;
        i++;
    }
    return color_return;
}
