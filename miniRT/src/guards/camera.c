#include "../../includes/main.h"

/**
    * C -50.0,0,20 0,0,1 70
    ∗ identifier: C
    ∗ x,y,z coordinates of vp: -50.0, 0, 20
    ∗ x,y,z normalized orientation vector: 0, 0, 1
    ∗ field of view: 70 (in degrees)
 */
t_camera *camera_guard(char **split, int line)
{
    t_camera    *res;
    char        **pos;
    char        **direction;
    t_tuple     *center;
    t_tuple     *dir;
    double      fov;

    if (split_len(split) != 4)
        throw_error("Invalid camera arguments at line: ", line, NULL);
    // res = create_camera(WIDTH, HEIGHT, 0);
    // if (!res)
    //     return (NULL);
    
    pos = ft_c_split(split[1], ",");
    if (split_len(pos) != 3)
        throw_error("Invalid position in line: ", line, split[1]);

    center = create_point(0, 0, 0);
    if (!center)
        throw_error("Memory allocation error at line: ", line, NULL);
    dir = create_vector(0, 0, 0);
    if (!dir)
        throw_error("Memory allocation error at line: ", line, NULL);
    center->x = double_guard(pos[0], line, DOUBLE_MIN, DOUBLE_MAX);
    center->y = double_guard(pos[1], line, DOUBLE_MIN, DOUBLE_MAX);
    center->z = double_guard(pos[2], line, DOUBLE_MIN, DOUBLE_MAX);

    direction = ft_c_split(split[2], ",");
    if (split_len(direction) != 3)
        throw_error("Invalid direction in line: ", line, split[2]);
    dir->x = double_guard(direction[0], line, -1, 1);
    dir->y = double_guard(direction[1], line, -1, 1);
    dir->z = double_guard(direction[2], line, -1, 1);

    fov = ft_atoi(split[3]);

    res = create_camera(WIDTH, HEIGHT, fov);
    if (!res)
        throw_error("Memory allocation error at line: ", line, NULL);
    res->pos = center;
    res->direction = dir;
    res->transform = view_transform(res->pos, create_vector(0, 0, 0) ,res->direction);

    // if (DEBUG)
    // {
    //     printf(YELLOW"Camera: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tdirection: %f, %f, %f\n", res->direction.x, res->direction.y, res->direction.z);
    //     printf("\tfov: %d\n", res->fov);
    // }

    return (res);
}
