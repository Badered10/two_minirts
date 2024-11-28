#include "main.h"

space_point_t   point_guard(char *str, int line)
{
    space_point_t res;
    char **split;

    split = ft_split(str, ",");

    if (split_len(split) != 3)
        throw_error("Invalid point arguments at line: ", line, str);

    res.x = double_guard(split[0], line, DOUBLE_MIN, DOUBLE_MAX);
    res.y = double_guard(split[1], line, DOUBLE_MIN, DOUBLE_MAX);
    res.z = double_guard(split[2], line, DOUBLE_MIN, DOUBLE_MAX);
    return (res);
}
