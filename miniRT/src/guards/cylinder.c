#include "../../includes/main.h"

/**
 * cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 * identifier: cy
 * coordinates of the center: 50.0,0.0,20.6
 * normalized orientation vector: 0.0,0.0,1.0 [-1, 1]
 * diameter: 14.2 [0, inf]
 * height: 21.42 [0, inf]
 * color: 10,0,255
 */
cylinder_t
*cylander_guard(char **split, int line)
{
    cylinder_t *res;

    if (split_len(split) != 6)
        throw_error("Invalid cylinder arguments at line: ", line, NULL);

    res = new_(sizeof(cylinder_t));

    res->pos = point_guard(split[1], line);
    res->normal = point_guard(split[2], line);
    res->diameter = double_guard(split[3], line, 0, DOUBLE_MAX);
    res->height = double_guard(split[4], line, 0, DOUBLE_MAX);
    res->color = color_guard(split[5], line);

    res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Cylinder: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tnormal: %f, %f, %f\n", res->normal.x, res->normal.y, res->normal.z);
    //     printf("\tdiameter: %f\n", res->diameter);
    //     printf("\theight: %f\n", res->height);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    insert_cylinder(res);
    return (res);
}
