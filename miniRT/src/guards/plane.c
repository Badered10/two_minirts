#include "../../includes/main.h"

/**
 * pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
 * identifier: pl
 * position of center: 0.0,0.0,-10.0
 * normalized orientation vector: 0.0,1.0,0.0
 * color: 0,0,225
 */

t_matrix *rotation(t_tuple *axis, double angle)
{
    t_matrix *matrix = create_matrix(4, 4, NULL);
    if (!matrix) return (NULL);

    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double one_minus_cos = 1 - cos_angle;

    // Normalize the rotation axis
    double axis_len = len_tuple(axis);
    double x = axis->x / axis_len;
    double y = axis->y / axis_len;
    double z = axis->z / axis_len;

    // Set the rotation matrix values
    matrix->data[0][0] = cos_angle + x * x * one_minus_cos;
    matrix->data[0][1] = x * y * one_minus_cos - z * sin_angle;
    matrix->data[0][2] = x * z * one_minus_cos + y * sin_angle;
    matrix->data[0][3] = 0;

    matrix->data[1][0] = y * x * one_minus_cos + z * sin_angle;
    matrix->data[1][1] = cos_angle + y * y * one_minus_cos;
    matrix->data[1][2] = y * z * one_minus_cos - x * sin_angle;
    matrix->data[1][3] = 0;

    matrix->data[2][0] = z * x * one_minus_cos - y * sin_angle;
    matrix->data[2][1] = z * y * one_minus_cos + x * sin_angle;
    matrix->data[2][2] = cos_angle + z * z * one_minus_cos;
    matrix->data[2][3] = 0;

    matrix->data[3][0] = 0;
    matrix->data[3][1] = 0;
    matrix->data[3][2] = 0;
    matrix->data[3][3] = 1;

    return matrix;
}


t_matrix *align_vector(t_tuple *v, t_tuple *target)
{
    t_tuple *up = create_vector(0, 1, 0); // or whatever up vector you want
    t_tuple *v_normalized = norm_tuple(v);
    t_tuple *target_normalized = norm_tuple(target);
    
    // Use the cross product to find the rotation axis
    t_tuple *axis = cross_tuple(v_normalized, target_normalized);
    double angle = acos(dot_tuple(v_normalized, target_normalized));

    // Create a rotation matrix around the axis
    t_matrix *rotation_matrix = rotation(axis, angle);

    // free_tuple(v_normalized);
    // free_tuple(target_normalized);
    // free_tuple(axis);

    return rotation_matrix;
}


t_matrix *plane_transform(t_tuple *pos, t_tuple *normal)
{
    t_matrix *rotation;
    t_matrix *trans;
    t_matrix *transform;

    // // Compute rotation matrix (align normal with (0,1,0))
    // rotation = align_vector(normal, create_vector(0, 1, 0));

    // Translate to correct position
    trans = translation(pos->x, pos->y, pos->z);

    // Final transform = Rotation * Translation
    // transform = matrix_multiply(rotation, trans, 4);

    // // Free temporary matrices
    // free_matrix(rotation);
    // free_matrix(trans);

    return (transform);
}


t_object
*plane_guard(char **split, int line)
{
    t_object *res;

    if (split_len(split) != 4)
        throw_error("Invalid plane arguments at line: ", line, NULL);

    res = create_object(PLANE);
    if (!res)
        throw_error("Failed to create plane: ", line, NULL);

    res->shape->plane->pos = point_guard(split[1], line);
    res->shape->plane->normal = point_guard(split[2], line);
    res->material->color = color_guard(split[3], line);
    res->shape->plane->normal->w = 0;
    // res->transform = plane_transform(res->shape->plane->pos, res->shape->plane->normal);
    // res->shape->plane->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Plane: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tnormal: %f, %f, %f\n", res->normal.x, res->normal.y, res->normal.z);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    // insert_plane(res);
    ft_lstadd_front(&scene()->objects_list, ft_lstnew(res));
    return (res);
}
