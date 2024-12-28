#include "color.h"

void write_color(const t_vec3 pixel_color)
{
    float r = pixel_color.x;
    float g = pixel_color.y;
    float b = pixel_color.z;

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    // Write out the pixel color components.
    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

t_color ray_color(t_ray r)
{
    t_vec3 unit_direction = vec3_unit(r.dir);
    float t = 0.5 * (unit_direction.y + 1.0);
    return vec3_add(vec3_scale(vec3(1.0, 1.0, 1.0), 1.0 - t), vec3_scale(vec3(0.5, 0.7, 1.0), t));
}
