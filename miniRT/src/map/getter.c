#include "main.h"

scene_t *scene()
{
    static scene_t scene_;
    return (&scene_);
}

void print_scene_data()
{
    for (light_t *light_list = scene()->light_list; light_list; light_list = light_list->next)
    {
        printf(YELLOW"Light: \n"RESET);
        printf("\tpos: %f, %f, %f\n", light_list->pos.x, light_list->pos.y, light_list->pos.z);
        printf("\tbrightness: %f\n", light_list->brightness);
        printf("\tcolor: %d, %d, %d\n", light_list->color.r, light_list->color.g, light_list->color.b);
    }
}
