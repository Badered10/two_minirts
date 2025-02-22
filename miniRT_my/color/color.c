#include "color.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../vec3/vec3.h"

typedef struct 
{
    t_point3 center;
    double radius;
} t_sphere;


double hit_sphere(t_point3 center, double radius, t_ray r)
{
    t_vec3 oc = vec3_sub(r.orig, center);
    double a = vec3_dot(r.dir, r.dir);
    double b = 2.0 * vec3_dot(r.dir, oc);
    double c = vec3_dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0)
        return (-1.0);
    else
    {
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t1 > 0.0)
            return t1;
        if (t2 > 0.0)
            return t2;
        return (-1.0);
    }
}

t_color int_to_t_color(int color)
{
    t_color pixel_color;

    pixel_color.x = (float)((color & 0x00FF0000) >> 16) / 255.0f;
    pixel_color.y = (float)((color & 0x0000FF00) >> 8) / 255.0f;
    pixel_color.z = (float)(color & 0x000000FF) / 255.0f;
    return pixel_color;
}

int t_color_to_int(t_color pixel_color)
{
    int r = (int)(255.0f * pixel_color.x);
    int g = (int)(255.0f * pixel_color.y);
    int b = (int)(255.0f * pixel_color.z);
    return (r << 16 | g << 8 | b);
}

void write_color(const t_vec3 pixel_color)
{
    float r = pixel_color.x;
    float g = pixel_color.y;
    float b = pixel_color.z;

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = (int)(255.0f * r);
    int gbyte = (int)(255.0f * g);
    int bbyte = (int)(255.0f * b);

    // Write out the pixel color components.
    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

t_color ray_color(t_ray r)
{
    double closest_t = 1e30;
    t_sphere *closest_sphere = NULL;

    t_vec3 unit_direction = vec3_unit(r.dir);
    float t = 0.5 * (unit_direction.y + 1.0);
    return vec3_add(vec3_scale(vec3(1.0, 1.0, 1.0), 1.0 - t), vec3_scale(vec3(0.5, 0.7, 1.0), t));
}
