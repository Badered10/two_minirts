#ifndef COLOR_H
#define COLOR_H

#include "../vec3/vec3.h"
#include "../ray/ray.h"
#include <stdio.h>

typedef t_vec3 t_color;
void    write_color(const t_vec3 pixel_color);
t_color ray_color(t_ray r);

#endif