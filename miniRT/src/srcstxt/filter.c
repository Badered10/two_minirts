#include "main.h"

double  dist(space_point_t *p1, space_point_t *p2)
{
    return (sqrt(
        pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2)
    ));
}

bool    is_in_fov(space_point_t *center)
{   
    double          angle_between;
    camera_t        *camera;

    camera = scene()->camera;
    // arccos( ( (CD^2) + (CP^2) - (PD ^ 2) ) / (2 * CD * CP) )
    angle_between = acos(
        (
            pow(dist(&camera->pos, &camera->direction), 2) +
            pow(dist(&camera->pos, center), 2) -
            pow(dist(center, &camera->direction), 2)
        )
        /
        (
            2*
            dist(&camera->pos, &camera->direction) *
            dist(&camera->pos, center)
        )
    );

    angle_between *= 180 / M_PI;

    if (angle_between < (camera->fov / 2))
        return true;

    return false;
}

