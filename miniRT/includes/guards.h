#ifndef GUARDS_H
#define GUARDS_H

#include "tools.h"
// utils
int             split_len(char **split);
double           double_guard(char *arg, int line, double min, double max);
t_tuple         *color_guard(char *color, int line);

t_tuple   *point_guard(char *str, int line);

t_ambient       *ambient_lighting_guard(char **split, int line);
t_camera        *camera_guard(char **split, int line);
t_light         *light_guard(char **split, int line);
t_object        *sphere_guard(char **split, int line_count);
t_object         *plane_guard(char **split, int line);
t_object      *cylander_guard(char **split, int line);

#endif