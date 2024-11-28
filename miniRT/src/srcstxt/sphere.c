#include "main.h"

/**
 * sp 0.0,0.0,20.6 12.6 10,0,255
 * identifier: sp
 * position of center: 0.0,0.0,20.6
 * diameter: 12.6
 * color: 10,0,255
*/
sphere_t
*sphere_guard(char **split, int line_count)
{
    sphere_t *res;

    if (split_len(split) != 4)
        throw_error("Invalid sphere arguments at line: ", line_count, NULL);

    res = new_(sizeof(sphere_t));

    res->pos = point_guard(split[1], line_count);
    res->diameter = double_guard(split[2], line_count, DOUBLE_MIN, DOUBLE_MAX);
    res->color = color_guard(split[3], line_count);

    res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Sphere: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tdiameter: %f\n", res->diameter);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    insert_sphere(res);
    return (res);
}
