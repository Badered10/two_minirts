#include "../../includes/main.h"

/**
    * A 0.2 255,255,255
    ∗ identifier: A
    ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
    ∗ R,G,B colors in range [0-255]: 255, 255, 255
 */

t_ambient *create_ambient_light(double lighting_ratio, t_tuple *color)
{
    t_ambient *res;

    res = new_(sizeof(t_ambient));
    if (!res)
        return (NULL);
    res->color = create_color(0, 0, 0);
    if (!res->color)
        return (free(res), NULL);
    res->lighting_ratio = lighting_ratio;
    res->color->x = color->x * lighting_ratio;
    res->color->y = color->y * lighting_ratio;
    res->color->z = color->z * lighting_ratio;


    // res->next = NULL;

    return (res);
}

t_ambient
*ambient_lighting_guard(char **split, int line)
{
    double          lighting_ratio;
    t_ambient       *res;
    t_tuple        *color;

    if (split_len(split) != 3)
       throw_error("Invalid arguments of ambient light in line: ", line, NULL);

    lighting_ratio = double_guard(split[1], line, 0, 1);
    (void)lighting_ratio;
    color = color_guard(split[2], line);
    // printf("color: %f, %f, %f\n", color->x, color->y, color->z);
    // exit(0);

    res = create_ambient_light(lighting_ratio, color);

    // if (DEBUG)
    // {
    //     printf(YELLOW"Ambient Light: \n"RESET);
    //     printf("\tlighting_ratio: %f\n", res->lighting_ratio);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    // insert_ambient_light(res);
    ft_lstadd_front(&scene()->ambient_list, ft_lstnew(res));
    return (res);
}


/**
    * L -40.0,50.0,0.0 0.6 10,0,255
    ∗ identifier: L
    ∗ x,y,z coordinates of the light source: -40.0, 50.0, 0.0
    ∗ the light brightness ratio in range [0.0,1.0]: 0.6
    ∗ R,G,B colors in range [0-255]: 10, 0, 255
 */
t_light
*light_guard(char **split, int line)
{
    t_light *res;

    if (split_len(split) != 4)
        throw_error("Invalid light arguments at line: ", line, NULL);

    // res = new_(sizeof(t_light));

    // res->position = point_guard(split[1], line);
    // res->brightness = double_guard(split[2], line, 0, 1);
    // res->color = color_guard(split[3], line);
    res = point_light(double_guard(split[2], line, 0, 1), point_guard(split[1], line), color_guard(split[3], line));
    // point_light(res->brightness, res->position, res->color);
    // res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Light: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tbrightness: %f\n", res->brightness);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    // insert_light(res);
    ft_lstadd_front(&scene()->lights_list, ft_lstnew(res));
    return res;
}