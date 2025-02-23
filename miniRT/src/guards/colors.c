#include "../../includes/main.h"

t_tuple *color_guard(char *color, int line)
{
    char    **color_idents;
    int     color_value;
    int     i;
    t_tuple *color_return;

    color_idents = ft_c_split(color, ",");
    i = 0;
    // ft_bzero(&color_return, sizeof(t_tuple));
    color_return = create_color(0, 0, 0);
    while (color_idents[i])
    {
        if (i > 2)
            throw_error("Unrespected RGB syntax at line: ", line, color);
        color_value = ft_atoi(color_idents[i]);
        if (color_value > 255 || color_value < 0)
            throw_error("Invalid color value [0, 255] in line: ", line, color_idents[i]);
        if (i == 0)
            color_return->x = color_value / 255.0;
        if (i == 1)
            color_return->y = color_value / 255.0;
        if (i == 2)
            color_return->z = color_value / 255.0;
        i++;
    }
    return color_return;
}
