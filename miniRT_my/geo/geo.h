#ifndef GEO_H
#define GEO_H

#include "../mlx_linux/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef EPSILON
#undef EPSILON
#endif

#ifdef POINT
#undef
#endif

#define POINT 1

#ifdef VEC
#undef
#endif

#define VEC 0

#define EPSILON 0.00001


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
    int width;
    int height;
    t_img *img;
} t_canvas;



t_tuple *creat_tuple(double x, double y, double z, double w);
t_tuple *creat_vector(double x, double y, double z);
t_tuple *creat_point(double x, double y, double z);
bool    equal(double a, double b);
bool    equal_tuple(t_tuple *a, t_tuple *b);
t_tuple *add_tuple(t_tuple *a, t_tuple *b);
t_tuple *sub_tuple(t_tuple *a, t_tuple *b);
t_tuple *negate_tuple(t_tuple *a);
t_tuple *mul_tuple(t_tuple *a, double b);
double  len_tuple(t_tuple *a);
t_tuple *norm_tuple(t_tuple *a);
double  dot_tuple(t_tuple *a, t_tuple *b);

#endif