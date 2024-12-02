#include "../../includes/main.h"

/**
 * pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
 * identifier: pl
 * position of center: 0.0,0.0,-10.0
 * normalized orientation vector: 0.0,1.0,0.0
 * color: 0,0,225
 */
plane_t
*plane_guard(char **split, int line)
{
    plane_t *res;

    if (split_len(split) != 4)
        throw_error("Invalid plane arguments at line: ", line, NULL);

    res = new_(sizeof(plane_t));

    res->pos = point_guard(split[1], line);
    res->normal = point_guard(split[2], line);
    res->color = color_guard(split[3], line);

    res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Plane: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tnormal: %f, %f, %f\n", res->normal.x, res->normal.y, res->normal.z);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    insert_plane(res);
    return (res);
}
