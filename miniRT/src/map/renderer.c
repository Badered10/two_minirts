#include "../../includes/main.h"

void    to_render()
{
    t_list    *object;

    // sphers check
    object = scene()->objects_list;
    while (object)
    {
        if (((t_object *)(object->content))->type == SPHERE)
        {
            if (is_in_fov(((t_object *)(object->content))->shape->sphere->pos)) // for sphere
                printf("Sphere-> {%f, %f, %f} will be rendered\n", (((t_object *)(object->content))->shape->sphere->pos)->x
                , (((t_object *)(object->content))->shape->sphere->pos)->y, 
                (((t_object *)(object->content))->shape->sphere->pos)->z);
        }
           object = object->next;
            
    }
}
