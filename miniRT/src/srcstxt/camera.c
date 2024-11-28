#include "main.h"

/**
    * C -50.0,0,20 0,0,1 70
    ∗ identifier: C
    ∗ x,y,z coordinates of vp: -50.0, 0, 20
    ∗ x,y,z normalized orientation vector: 0, 0, 1
    ∗ field of view: 70 (in degrees)
 */
camera_t
*camera_guard(char **split, int line)
{
    camera_t    *res;
    char        **pos;
    char        **direction;

    if (split_len(split) != 4)
        throw_error("Invalid camera arguments at line: ", line, NULL);
    res = new_(sizeof(camera_t));

    pos = ft_split(split[1], ",");
    if (split_len(pos) != 3)
        throw_error("Invalid position in line: ", line, split[1]);

    res->pos.x = double_guard(pos[0], line, DOUBLE_MIN, DOUBLE_MAX);
    res->pos.y = double_guard(pos[1], line, DOUBLE_MIN, DOUBLE_MAX);
    res->pos.z = double_guard(pos[2], line, DOUBLE_MIN, DOUBLE_MAX);

    direction = ft_split(split[2], ",");
    if (split_len(direction) != 3)
        throw_error("Invalid direction in line: ", line, split[2]);
    res->direction.x = double_guard(direction[0], line, -1, 1);
    res->direction.y = double_guard(direction[1], line, -1, 1);
    res->direction.z = double_guard(direction[2], line, -1, 1);

    res->fov = ft_atoi(split[3]);

    // if (DEBUG)
    // {
    //     printf(YELLOW"Camera: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tdirection: %f, %f, %f\n", res->direction.x, res->direction.y, res->direction.z);
    //     printf("\tfov: %d\n", res->fov);
    // }

    return (res);
}
