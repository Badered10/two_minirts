#ifndef GUARDS_H
#define GUARDS_H

// utils
int             split_len(char **split);
double           double_guard(char *arg, int line, double min, double max);
color_t         color_guard(char *color, int line);

space_point_t   point_guard(char *str, int line);

ambient_light_t *ambient_lighting_guard(char **split, int line);
camera_t        *camera_guard(char **split, int line);
light_t         *light_guard(char **split, int line);
sphere_t        *sphere_guard(char **split, int line_count);
plane_t         *plane_guard(char **split, int line);
cylinder_t      *cylander_guard(char **split, int line);

#endif