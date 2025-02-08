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

#define EPSILON 0.00000000000000000000000000000000001
#define PI 3.14159265358979323846264338327950


typedef enum s_type
{
    SPHERE
} e_type;

typedef struct s_tuple
{
    double x; // C : 0 - 1 -> 0 - 255 // R
    double y; //  :  // G
    double z; //  // B
    int w; // 0 1 20
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
    t_tuple *origin; // point
    t_tuple *direction; // vector
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
    bool material_seted;
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
    t_tuple *position; // point
    t_tuple *intensity; // color RGB A
} t_light;




t_tuple *create_tuple(double x, double y, double z, double w, t_list **garbge);
t_tuple *create_vector(double x, double y, double z, t_list **garbge);
t_tuple *create_point(double x, double y, double z, t_list **garbge);
bool    equal(double a, double b);
bool    equal_tuple(t_tuple *a, t_tuple *b);
t_tuple *add_tuple(t_tuple *a, t_tuple *b, t_list **garbge);
t_tuple *sub_tuple(t_tuple *a, t_tuple *b, t_list **garbge);
t_tuple *negate_tuple(t_tuple *a, t_list **garbge);
t_tuple *mul_tuple(t_tuple *a, double b, t_list **garbge);
double  len_tuple(t_tuple *a);
t_tuple *norm_tuple(t_tuple *a, t_list **garbge);
double  dot_tuple(t_tuple *a, t_tuple *b);
double matrix_determinant(t_matrix *matrix, t_list **garbge);
double matrix_minor(t_matrix *matrix, int row, int column, t_list **garbge);
double matrix_cofactor(t_matrix *matrix, int row, int column, t_list **garbge);
t_ray *transform(t_ray *ray, t_matrix *matrix, t_list **garbge);
t_material *create_material(t_list **garbge);
void free_material(t_material *m);
void add_to_garbge(t_list **garbge, void *adress);
void *safe_malloc(size_t size, t_list **garbge);

#endif