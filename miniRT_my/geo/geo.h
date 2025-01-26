#ifndef GEO_H
#define GEO_H

#include "../mlx_linux/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

#define EPSILON 0.00001
#define PI 3.14159265359


typedef enum s_type
{
    SPHERE
} e_type;

typedef struct s_tuple
{
    double x;
    double y;
    double z;
    int w;
} t_tuple;

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

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

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

typedef struct s_shearing
{
    double xy;
    double xz;
    double yx;
    double yz;
    double zx;
    double zy;
} t_shearing;

typedef struct s_ray
{
    t_tuple *origin;
    t_tuple *direction;
} t_ray;

typedef struct s_material
{
    t_tuple *color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} t_material;

typedef struct s_sphere
{
    t_tuple *center;
    t_matrix *transform;
    t_material *material;
    double r;
} t_sphere;


typedef union s_shape
{
    t_sphere *sphere;
} t_shape;

typedef struct s_object
{
    t_shape *shape;
    e_type type;
} t_object;

typedef struct s_intersect
{
    t_object *object;
    int     count;
    int     t1;
    int     t2;
} t_intersect;

typedef struct s_intersection
{
    double t;
    t_object *object;
} t_intersection;

typedef struct s_light
{
    t_tuple *position;
    t_tuple *intensity;
} t_light;




t_tuple *create_tuple(double x, double y, double z, double w);
t_tuple *create_vector(double x, double y, double z);
t_tuple *create_point(double x, double y, double z);
bool    equal(double a, double b);
bool    equal_tuple(t_tuple *a, t_tuple *b);
t_tuple *add_tuple(t_tuple *a, t_tuple *b);
t_tuple *sub_tuple(t_tuple *a, t_tuple *b);
t_tuple *negate_tuple(t_tuple *a);
t_tuple *mul_tuple(t_tuple *a, double b);
double  len_tuple(t_tuple *a);
t_tuple *norm_tuple(t_tuple *a);
double  dot_tuple(t_tuple *a, t_tuple *b);
double matrix_determinant(t_matrix *matrix);
double matrix_minor(t_matrix *matrix, int row, int column);
double matrix_cofactor(t_matrix *matrix, int row, int column);
t_ray *transform(t_ray *ray, t_matrix *matrix);
t_material *create_material(void);
#endif