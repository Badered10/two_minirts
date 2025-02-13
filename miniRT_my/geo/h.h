#ifndef H_H
#define H_H

#include "../mlx_linux/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"
#include "get_next_line.h"


#ifdef EPSILON
#undef EPSILON
#endif

#ifdef PI
#undef PI
#endif

#ifdef POINT
#undef POINT
#endif

#define POINT 1

#ifdef VEC
#undef VEC
#endif

#define VEC 0

#define EPSILON 0.0001
#define PI 3.141592653589793238

typedef enum s_type
{
    SPHERE,
    PLANE,
    CYLINDER
} e_type;

typedef struct s_tuple
{
    double x;
    double y;
    double z;
    double w;
} t_tuple;

typedef struct s_img 
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_canvas
{
    void *mlx;
    int width;
    int height;
    t_img *img;
} t_canvas;

typedef struct s_matrix
{
    int size;
    double **data;
} t_matrix;

typedef struct s_ray
{
    t_tuple *origin;
    t_tuple *direction;
} t_ray;

typedef struct s_material
{
    t_tuple *color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

typedef struct s_sphere
{
    t_tuple *center;
    t_matrix *transform;
    t_material *material;
    double r;
} t_sphere;

typedef struct s_plane
{
    t_tuple *point;
    t_tuple *normal;
    t_matrix *transform;
    t_material *material;
} t_plane;

typedef struct s_cylinder
{
    t_tuple *center;
    t_tuple *axis;
    double radius;
    double height;
    t_matrix *transform;
    t_material *material;
} t_cylinder;

typedef union s_shape
{
    t_sphere *sphere;
    t_plane *plane;
    t_cylinder *cylinder;
} t_shape;

typedef struct s_object
{
    t_shape *shape;
    e_type type;
} t_object;

typedef struct s_intersect
{
    t_object *object;
    double t;
} t_intersect;

typedef struct s_xs
{
    t_intersect *inters;
    int count; // total of inters;
} t_xs;

typedef struct s_light
{
    t_tuple *position;
    t_tuple *intensity;
} t_light;

typedef struct s_world
{
    t_list *lights_list;
    t_list *objects_list;
    double ambient_light;
    t_tuple *ambient_color;
} t_world;

typedef struct s_comps
{
    double t;
    t_object *object;
    t_tuple *point;
    t_tuple *eyev;
    t_tuple *normalv;
    bool inside;
    t_tuple *over_point;
} t_comps;

typedef struct s_camera
{
    double hsize;
    double vsize;
    double field_of_view;
    double half_width;
    double half_height;
    double pixel_size;
    t_matrix *transform;
} t_camera;

typedef struct projectile
{
    t_tuple *position;
    t_tuple *speed;
} t_projectile;
typedef struct environment
{
    t_tuple *gravity;
    t_tuple *wind;
} t_environment;

typedef struct s_shearing
{
    double xy;
    double xz;
    double yx;
    double yz;
    double zx;
    double zy;
} t_shearing;

// Function Declarations
t_tuple *create_tuple(double x, double y, double z, double w);
t_tuple *create_vector(double x, double y, double z);
t_tuple *create_point(double x, double y, double z);
bool equal(double a, double b);
bool equal_tuple(t_tuple *a, t_tuple *b);
t_tuple *add_tuple(t_tuple *a, t_tuple *b);
t_tuple *sub_tuple(t_tuple *a, t_tuple *b);
t_tuple *negate_tuple(t_tuple *a);
t_tuple *mul_tuple(t_tuple *a, double b);
double len_tuple(t_tuple *a);
t_tuple *norm_tuple(t_tuple *a);
double dot_tuple(t_tuple *a, t_tuple *b);
double matrix_determinant(t_matrix *matrix);
double matrix_minor(t_matrix *matrix, int row, int column);
double matrix_cofactor(t_matrix *matrix, int row, int column);
t_ray *transform(t_ray *ray, t_matrix *matrix);
t_material *create_material(void);
t_matrix *create_matrix(int rows, int colums, const double **arr);
t_matrix *scaling(double x, double y, double z);
t_matrix *translation(double x, double y, double z);
t_matrix *rotation_x(double radians);
t_matrix *rotation_y(double radians);
t_matrix *rotation_z(double radians);
t_matrix *matrix_multiply(t_matrix *a, t_matrix *b, int size);
t_world *create_world(void);
t_camera *create_camera(int hsize, int vsize, double field_of_view);
t_canvas *render(t_camera *cam, t_world *world, void *mlx, void *win);
t_light *point_light(t_tuple *position, t_tuple *intensity);
t_matrix *view_transform(t_tuple *from, t_tuple *to, t_tuple *up);
t_object *create_object(e_type type);
t_sphere *create_sphere(void);
t_tuple *create_color(double x, double y, double z);
void parse_file(const char *filename, t_world *world, t_camera **cam);
bool is_shadowed(t_world *world, t_tuple *point);
t_xs *intersect(t_object *object, t_ray *ray);
// t_object *create_plane(void);
// t_object *create_cylinder(void);

#endif