#include "../../includes/main.h"

double  dist(t_tuple *p1, t_tuple *p2)
{
    return (sqrt(
        pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2)
    ));
}

bool    is_in_fov(t_tuple *center)
{   
    double          angle_between;
    t_camera        *camera;

    camera = scene()->camera;
    // arccos( ( (CD^2) + (CP^2) - (PD ^ 2) ) / (2 * CD * CP) )
    angle_between = acos(
        (
            pow(dist(camera->pos, camera->direction), 2) +
            pow(dist(camera->pos, center), 2) -
            pow(dist(center, camera->direction), 2)
        )
        /
        (
            2*
            dist(camera->pos, camera->direction) *
            dist(camera->pos, center)
        )
    );

    angle_between *= 180 / M_PI;

    if (angle_between < (camera->field_of_view / 2))
        return true;

    return false;
}

