#include "../../includes/main.h"

t_tuple   *point_guard(char *str, int line)
{
    t_tuple *res;
    char **split;

    split = ft_c_split(str, ",");

    if (split_len(split) != 3)
        throw_error("Invalid point arguments at line: ", line, str);
    res = create_point(0, 0, 0);
    if (!res)
        return (NULL);
    res->x = double_guard(split[0], line, DOUBLE_MIN, DOUBLE_MAX);
    res->y = double_guard(split[1], line, DOUBLE_MIN, DOUBLE_MAX);
    res->z = double_guard(split[2], line, DOUBLE_MIN, DOUBLE_MAX);
    return (res);
}
