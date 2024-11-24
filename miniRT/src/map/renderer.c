#include "main.h"

void    render()
{
    sphere_t    *sphere;

    // sphers check
    sphere = scene()->sphere_list;
    while (sphere)
    {
        if (is_in_fov(&sphere->pos))
            printf("Sphere-> {%f, %f, %f} will be rendered\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
        sphere = sphere->next;
    }
}
