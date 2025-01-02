#ifndef GEO_H
#define GEO_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef EPSILON
#undef EPSILON
#endif

#define EPSILON 0.00001


typedef struct s_tuple
{
    double x;
    double y;
    double z;
    int w;
} t_tuple;

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