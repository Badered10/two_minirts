#ifndef TOOLS_H
#define TOOLS_H

# include "libs.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct flat_point_s
{
    double     x;
    double     y;
}   flat_point_t;

typedef struct space_point_s
{
    double     x;
    double     y;
    double     z;
}   space_point_t;

typedef struct color_s
{
    unsigned short  r;
    unsigned short  g;
    unsigned short  b;
}   color_t;

typedef struct ambient_light_s
{
    double   lighting_ratio;
    color_t color;
    struct ambient_light_s *next;
}   ambient_light_t;

typedef struct camera_s
{
    space_point_t   pos;
    space_point_t   direction;
    int             fov;
}   camera_t;

typedef struct light_s
{
    space_point_t   pos;
    double           brightness;
    color_t         color;
    struct light_s  *next;
}   light_t;

typedef struct sphere_s
{
    space_point_t   pos;
    double           diameter;
    color_t         color;
    struct sphere_s *next;
}   sphere_t;

typedef struct plane_s
{
    space_point_t   pos;
    space_point_t   normal; // [-1, 1] [-1, 1] [-1, 1]
    color_t         color;
    struct plane_s  *next;
}   plane_t;

typedef struct cylinder_s
{
    space_point_t       pos;
    space_point_t       normal; // [-1, 1] [-1, 1] [-1, 1]
    double               diameter;
    double               height;
    color_t             color;
    struct cylinder_s   *next;
}   cylinder_t;

typedef struct scene_s
{
    camera_t                *camera;
    ambient_light_t         *ambient_light_list;
    light_t                 *light_list;
    sphere_t                *sphere_list;
    plane_t                 *plane_list;
    cylinder_t              *cylinder_list;
}   scene_t;

typedef struct ray_s
{
    space_point_t   origin;
    space_point_t   direction;
    double          t;
    color_t         color;
}   ray_t;

#endif