#include "../../includes/main.h"

/**
 * sp 0.0,0.0,20.6 12.6 10,0,255
 * identifier: sp
 * position of center: 0.0,0.0,20.6
 * diameter: 12.6
 * color: 10,0,255
*/

t_object *sphere_guard(char **split, int line_count)
{
    t_object *res;
    t_matrix *scale;
    t_matrix *trans;

    if (split_len(split) != 4)
        throw_error("Invalid sphere arguments at line: ", line_count, NULL);

    res = create_object(SPHERE);
    if (res == NULL)
        return (NULL);

    res->shape->sphere->pos = point_guard(split[1], line_count);
    res->shape->sphere->diameter = double_guard(split[2], line_count, DOUBLE_MIN, DOUBLE_MAX);
    res->material->color = color_guard(split[3], line_count);

    scale = scaling(res->shape->sphere->diameter / 2,
                            res->shape->sphere->diameter / 2,
                            res->shape->sphere->diameter / 2);

    trans = translation(res->shape->sphere->pos->x,
                                    res->shape->sphere->pos->y,
                                    res->shape->sphere->pos->z);

    res->transform  = matrix_multiply(trans, scale, 4);

    // free_matrix(scale);
    // free_matrix(trans);


    // res->shape->sphere->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Sphere: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tdiameter: %f\n", res->diameter);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    // insert_sphere(res);
    ft_lstadd_front(&scene()->objects_list, ft_lstnew(res));
    return (res);
}
