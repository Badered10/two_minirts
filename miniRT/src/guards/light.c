#include "main.h"

/**
    * A 0.2 255,255,255
    ∗ identifier: A
    ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
    ∗ R,G,B colors in range [0-255]: 255, 255, 255
 */
ambient_light_t
*ambient_lighting_guard(char **split, int line)
{
    double           lighting_ratio;
    ambient_light_t *res;
    color_t         color;

    if (split_len(split) != 3)
       throw_error("Invalid arguments of ambient light in line: ", line, NULL);

    lighting_ratio = double_guard(split[1], line, 0, 1);
    (void)lighting_ratio;
    color = color_guard(split[2], line);

    res = new_(sizeof(ambient_light_t));
    res->lighting_ratio = lighting_ratio;
    res->color.r = color.r;
    res->color.g = color.g;
    res->color.b = color.b;
    res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Ambient Light: \n"RESET);
    //     printf("\tlighting_ratio: %f\n", res->lighting_ratio);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    insert_ambient_light(res);
    return (res);
}


/**
    * L -40.0,50.0,0.0 0.6 10,0,255
    ∗ identifier: L
    ∗ x,y,z coordinates of the light source: -40.0, 50.0, 0.0
    ∗ the light brightness ratio in range [0.0,1.0]: 0.6
    ∗ R,G,B colors in range [0-255]: 10, 0, 255
 */
light_t
*light_guard(char **split, int line)
{
    light_t *res;

    if (split_len(split) != 4)
        throw_error("Invalid light arguments at line: ", line, NULL);

    res = new_(sizeof(light_t));

    res->pos = point_guard(split[1], line);
    res->brightness = double_guard(split[2], line, 0, 1);
    res->color = color_guard(split[3], line);
    res->next = NULL;

    // if (DEBUG)
    // {
    //     printf(YELLOW"Light: \n"RESET);
    //     printf("\tpos: %f, %f, %f\n", res->pos.x, res->pos.y, res->pos.z);
    //     printf("\tbrightness: %f\n", res->brightness);
    //     printf("\tcolor: %d, %d, %d\n", res->color.r, res->color.g, res->color.b);
    // }

    insert_light(res);
    return res;
}