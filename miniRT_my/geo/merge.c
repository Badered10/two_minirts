/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:17:09 by baouragh          #+#    #+#             */
/*   Updated: 2025/02/19 18:56:20 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/libft.h"
// #include "h.h"
#include "/home/baouragh/Desktop/two_minirts/miniRT/src/../includes/main.h"

#define WIDTH 200
#define HEIGHT 100
// DEBUG FUNCTION-------------------------------------------------------------------------------
void print_type(t_tuple *tuple)
{
    if (!tuple)
        return (printf("ERR TUPLE NULL\n"), (void)0);
    if (tuple->w == 0)
        printf("is Vector : x = %f, y = %f, z = %f, w = %f\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else if (tuple->w == 1)
        printf("is Point : x = %f, y = %f, z = %f , w = %f\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else if (tuple->w == 20)
        printf("is Color : x = %f, y = %f, z = %f , w = %f\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else
        printf("is Undefined : x = %f, y = %f, z = %f , w = %f\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
}

// CREATE A TUPLE STRUCTURE---------------------------------------------------------------------
t_tuple *create_tuple(double x, double y, double z, double w)
{
    t_tuple *tuple;
    tuple = malloc(sizeof(t_tuple));
    if (tuple == NULL)
        return (NULL);

    tuple->x = x;
    tuple->y = y;
    tuple->z = z;
    tuple->w = w;

    return (tuple);
}

t_tuple *create_point(double x, double y, double z)
{
    return (create_tuple(x, y, z, 1));
}

t_tuple *create_vector(double x, double y, double z)
{
    return (create_tuple(x, y, z, 0));
}

t_tuple *create_color(double x, double y, double z)
{
    return (create_tuple(x, y, z, 20));
}

// ARTHEMATIC FUNCTIONS-------------------------------------------------------------------------

bool equal(double a, double b)
{
    if (fabs(a - b) < EPSILON)
        return (true);
    else
        return (false);
}

bool equal_tuple(t_tuple *a, t_tuple *b)
{
    if (equal(a->x, b->x) && equal(a->y, b->y) && equal(a->z, b->z) && a->w == b->w)
        return (true);
    else
        return (false);
}

t_tuple *add_tuple(t_tuple *a, t_tuple *b)
{
    double w;

    if (a->w != 20 && b->w != 20)
        w = a->w + b->w;
    else
        w = 20;
    return (create_tuple(a->x + b->x, a->y + b->y, a->z + b->z, w));
}

t_tuple *sub_tuple(t_tuple *a, t_tuple *b)
{
    return (create_tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w));
}

t_tuple *negate_tuple(t_tuple *a)
{
    return (create_tuple(-a->x, -a->y, -a->z, -a->w));
}

t_tuple *mul_tuple(t_tuple *a, double b)
{
    return (create_tuple(a->x * b, a->y * b, a->z * b, a->w * b));
}

t_tuple *div_tuple(t_tuple *a, double b)
{
    return (create_tuple(a->x / b, a->y / b, a->z / b, a->w / b));
}
double len_tuple(t_tuple *a)
{
    return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}
t_tuple *norm_tuple(t_tuple *a)
{
    return (div_tuple(a, len_tuple(a)));
}

double dot_tuple(t_tuple *a, t_tuple *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_tuple *cross_tuple(t_tuple *a, t_tuple *b)
{
    return (create_vector(a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x));
}

t_tuple *hadamard_product(t_tuple *a, t_tuple *b)
{
    return (create_color(a->x * b->x, a->y * b->y, a->z * b->z));
}

// PROJECTILE FUNCS--------------------------------------------------------------------------

t_projectile *create_projectile(t_tuple *position, t_tuple *speed)
{
    t_projectile *projectile = malloc(sizeof(t_projectile));
    if (projectile == NULL)
        return (NULL);

    projectile->position = position;
    projectile->speed = speed;

    return (projectile);
}

t_environment *create_environment(t_tuple *gravity, t_tuple *wind)
{
    t_environment *environment = malloc(sizeof(t_environment));
    if (environment == NULL)
        return (NULL);

    environment->gravity = gravity;
    environment->wind = wind;

    return (environment);
}

t_projectile *tick(t_environment *env, t_projectile *projectile)
{
    t_tuple *position = add_tuple(projectile->position, projectile->speed);
    t_tuple *speed = add_tuple(add_tuple(projectile->speed, env->gravity), env->wind);

    return (create_projectile(position, speed));
}

// MLX MY--------------------------------------------------------------------------------------

t_img *new_img( int width, int height, void *mlx)
{
    t_img *img;

    img = malloc(sizeof(t_img));
    if (!img)
        return (NULL);
    img->img = mlx_new_image(mlx, width, height);
    if (!img->img)
        return (NULL);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    if (!img->addr)
        return (NULL);
    return (img);
}

t_canvas * create_canvas(int width , int height, void *mlx_ptr)
{
    t_canvas *canvas;

    if (!mlx_ptr)
        return (NULL);
    canvas = malloc(sizeof(t_canvas));
    if (!canvas)
        return (NULL);
    canvas->mlx = mlx_ptr;
    canvas->width = width;
    canvas->height = height;
    canvas->img = new_img(width, height, mlx_ptr);
    if (!canvas->img)
        return (NULL);
    return (canvas);
}

int color_at_cords (t_img *img, int x, int y)
{
    char    *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

int check_color (t_img *img, int x, int y, int color)
{
    char    *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst == (unsigned int) color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *dst;
    
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int color_to_int(t_tuple *color)
{
    int r;
    int g;
    int b;

    if (!color)
        return (1);
    r = color->x * 255;
    g = color->y * 255;
    b = color->z * 255;

    if (r > 255)
        r = 255;
        else if (r < 0)
            r = 0;
    if (g > 255)
        g = 255;
        else if (g < 0)
            g = 0;
    if (b > 255)
        b = 255;
        else if (b < 0)
            b = 0;

    return ((r << 16) | (g << 8) | (b)); // ff ff ff
}

t_tuple * int_to_color(int color)
{
    double r;
    double g;
    double b;

    r = ((color >> 16) & 0XFF) / 255.0;
    g = ((color >> 8) & 0XFF) / 255.0;
    b = (color & 0XFF) / 255.0;

    return (create_color(r, g, b));
}

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color)
{
    my_mlx_pixel_put(canvas->img, x, y, color_to_int(color));
}

t_tuple *pixel_at(t_canvas *canvas, int x, int y)
{ 
    int color;

    color = color_at_cords(canvas->img, x, y);
    return (int_to_color(color));
}

// MATRIXS INTO THE SCENE------------------------------------------------------------

void free_old(double **res, int i)
{
    if (!res)
        return ;
    while (i >= 0)
    {
        free(res[i]);
        i--;
    }
    free(res);
}

double **create_arr(int rows, int cols)
{
    double **res;
    int i;

    res = malloc(sizeof(double *) * rows);
    if (!res)
        return (NULL);
    i = -1;
    while (++i < cols)
    {
        res[i] = malloc(sizeof(double) * cols);
        if (!res[i])
            return( free_old(res, i), NULL);
    }
    return (res);
}

void free_matrix(t_matrix *matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return;
    while (i < matrix->size)
    {
        free(matrix->data[i]);
        i++;
    }
    free(matrix->data);
    free(matrix);
}


double **set_zeros(int rows, int colums)
{
    int i;
    int j;
    double **res;

    if (rows <= 0 || colums <= 0)
        return (NULL);
    res = malloc(rows * sizeof(double *));
    if (!res)
        return (NULL);
    i = 0;
    while (i < rows)
    {
        res[i] = malloc(colums * sizeof(double));
        if (!res[i])
            return (free_old(res, i - 1) ,NULL);
        j = 0;
        while(j < colums)
        {
            res[i][j] = 0.0;
            j++;
        }
        i++;
    }
    return (res);
}

double **duplicate_array(int rows, int colums, const double **arr)
{
    int i;
    int j;
    double **res;

    if (!arr || !*arr || rows <= 0 || colums <= 0)
        return (NULL);
    res = malloc(rows * sizeof(double *));
    if (!res)
        return (NULL);
    i = 0;
    while (i < rows)
    {
        res[i] = malloc(colums * sizeof(double));
        if (!res[i])
            return (free_old(res, i - 1) ,NULL);
        j = 0;
        while(j < colums)
        {
            res[i][j] = arr[i][j];
            j++;
        }
        i++;
    }
    return (res);
}

t_matrix *create_matrix(int rows, int colums, const double **arr)
{
    t_matrix *matrix;

    if (rows <= 0 || colums <= 0 || rows != colums)
        return (NULL);
    matrix = malloc(sizeof(t_matrix));
    if (!matrix)
        return (NULL);
    matrix->size = rows;
    if (!arr || !*arr)
    {
        matrix->data = set_zeros(rows, colums);
        if (!matrix->data)
            return (free(matrix), NULL);
        return (matrix);
    }
    matrix->data = duplicate_array(rows, colums, arr);
    if (!matrix->data)
        return (free(matrix), NULL);
    return (matrix);
}

double matrix_at(t_matrix *m, int i, int j)
{
    if (i > m->size || i < 0 || j > m->size || j < 0)
        return (printf("ERROR : MATRIX OUT OF RANGE\n"), -1);

    return (m->data[i][j]);    
}

void print_matrix(t_matrix *m)
{
    int i;
    int j;

    i = 0;
    while (i < m->size)
    {
        j = 0;
        while (j < m->size)
        {
            printf("M[%d][%d] = %f ",i ,j ,matrix_at(m, i, j));
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
}

//MATRIX ARTHEMATIC ----------------------------------------------------------------------

bool matrix_equal(t_matrix *m1, t_matrix *m2)
{
    int i;
    int j;

    if (!m1 || !m2 || !m1->data || !m2->data ||
         m1->size != m2->size)
        return (0);
    i = 0;
    while (i < m1->size)
    {
        j = 0;
        while (j < m1->size)
        {
            if (!equal(matrix_at(m1, i, j), matrix_at(m2, i, j)))
            {
                printf("diff M1[%d][%d] = %f, M2[%d][%d] = %f\n",i,j,
                    matrix_at(m1, i, j), i, j, matrix_at(m2, i, j));
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);   
}

t_matrix *matrix_multiply(t_matrix *a, t_matrix *b, int size) // JUST FOR 4X4 matrixs 
{
    t_matrix *matrix;
    int i;
    int j;

    if (!a || !b || !a->data || !b->data || a->size != size || b->size != size)
        return (0);
    matrix = create_matrix(size, size, NULL);
    if (!matrix)
        return (NULL);
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            matrix->data[i][j] =  a->data[i][0] * b->data[0][j] 
                                + a->data[i][1] * b->data[1][j] 
                                + a->data[i][2] * b->data[2][j]
                                + a->data[i][3] * b->data[3][j];
            j++;
        }
        i++;
    }
    return (matrix);
}

t_tuple *matrix_tuple_mul4x4(t_matrix *a, t_tuple *t) // JUST FOR 4X4 matrixs 
{
    t_tuple *tuple;
    int i;
    double res;

    if (!a || !t || !a->data || a->size != 4)
        return (NULL);
    tuple = create_tuple(0, 0, 0, 0);
    i = 0;
    while (i < 4)
    {
        res =     a->data[i][0] * t->x
                + a->data[i][1] * t->y 
                + a->data[i][2] * t->z
                + a->data[i][3] * t->w;
        if (i == 0)
            tuple->x = res;
        else if (i == 1)
            tuple->y = res;
        else if (i == 2)
            tuple->z = res;
        else
            tuple->w = res;
        i++;
    }
    return (tuple);
}

t_matrix *matrix_transpose4x4(t_matrix *matrix)
{
    t_matrix *trans;
    int i;
    int j;

    if (!matrix || !matrix->data)
        return (NULL);
    trans = create_matrix(4, 4 , NULL);
    if (!trans)
        return (NULL);
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            trans->data[i][j] = matrix->data[j][i];
            j++;
        }
        i++;
    }
    return (trans);
}


void remove_row_cols(t_matrix *matrix, t_matrix *submatrix, int row, int column)
{
    int i;
    int j;
    int new_row;
    int new_col;

    i = -1;
    new_row = 0;
    while (++i < matrix->size)
    {
        j = -1;
        new_col = 0;
        if (i != row)
        {
            while (++j < matrix->size)
            {
                if (j != column)
                {
                    submatrix->data[new_row][new_col] = matrix->data[i][j];
                    new_col++;
                }
            }
            new_row++;
        }
    }
}

t_matrix *sub_matrix(t_matrix *matrix, int row, int column)
{
    t_matrix *submatrix;

    if (!matrix || !matrix->data || matrix->size <= column || matrix->size <= row)
        return (NULL);
    submatrix = create_matrix(matrix->size - 1, matrix->size - 1, NULL);
    if (!submatrix)
        return (NULL);
    remove_row_cols(matrix ,submatrix, row, column);
    return (submatrix);
}

double matrix_cofactor(t_matrix *matrix, int row, int column)
{
    double cofactor;

    cofactor = matrix_minor(matrix, row, column);
    if ((row + column) % 2)
        return (-cofactor);
    return (cofactor);
}

double matrix_determinant(t_matrix *matrix)
{
    double determinant;
    int    j;

    if (!matrix || !matrix->data)
        return 0;
    j = -1;
    determinant = 0;
    if (matrix->size == 2)
        determinant = (matrix->data[0][0] * matrix->data[1][1]) - (matrix->data[0][1] * matrix->data[1][0]);
    else
    {
        while (++j < matrix->size)
            determinant += matrix_cofactor(matrix, 0, j) * matrix->data[0][j];
    }
    return (determinant);
}

double matrix_minor(t_matrix *matrix, int row, int column)
{
    t_matrix *sub;
    double  minor;

    if (!matrix || !matrix->data)
        return (0);
    sub = sub_matrix(matrix, row, column);
    if (!sub)
        return (0);
    minor = matrix_determinant(sub);
    free_matrix(sub);
    return (minor);
}

bool matrix_invertiblity(t_matrix *matrix)
{
    double determinant;

    determinant = matrix_determinant(matrix);
    return ((fabs(determinant) > EPSILON));
}

t_matrix *matrix_inverse(t_matrix *matrix)
{
    t_matrix *inverse;
    double cofactor;
    double determinant;
    int row;
    int col;

    if (!matrix || !matrix->data)
        return (NULL);
    inverse = create_matrix(matrix->size, matrix->size, NULL);
    if (!inverse)
        return (NULL);
    determinant = matrix_determinant(matrix);
    row = -1;
    while (++row < matrix->size)
    {
        col = -1;
        while (++col < matrix->size)
        {
            cofactor = matrix_cofactor(matrix, row, col);
            inverse->data[col][row] = cofactor / determinant;
        }
    }
    return (inverse);
}

t_matrix* translation(double x, double y, double z)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);
    matrix->data[0][0] = 1;
    matrix->data[1][1] = 1;
    matrix->data[2][2] = 1;
    matrix->data[3][3] = 1;
    matrix->data[0][3] = x;
    matrix->data[1][3] = y;
    matrix->data[2][3] = z;
    return (matrix);
}

t_matrix *scaling(double x, double y, double z)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);
    matrix->data[0][0] = x;
    matrix->data[1][1] = y;
    matrix->data[2][2] = z;
    matrix->data[3][3] = 1;
    return (matrix);
}

double deg_to_rad(double deg)
{
    return ((deg / 180) * PI);
}

double rad_to_deg(double rad)
{
    return ((rad / PI) * 180);
}

t_matrix *rotation_x(double rad)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);

    matrix->data[0][0] = 1;
    matrix->data[3][3] = 1;
    
    matrix->data[1][1] = cos(rad);
    matrix->data[1][2] = -sin(rad);
    matrix->data[2][1] = sin(rad);
    matrix->data[2][2] = cos(rad);
    return (matrix);
}

t_matrix *rotation_y(double rad)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);

    matrix->data[3][3] = 1;
    matrix->data[1][1] = 1;
    
    matrix->data[0][0] = cos(rad);
    matrix->data[0][2] = sin(rad);
    matrix->data[2][0] = -sin(rad);
    matrix->data[2][2] = cos(rad);
    return (matrix);
}

t_matrix *rotation_z(double rad)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);

    matrix->data[3][3] = 1;
    matrix->data[2][2] = 1;
    
    matrix->data[0][0] = cos(rad);
    matrix->data[0][1] = -sin(rad);
    matrix->data[1][0] = sin(rad);
    matrix->data[1][1] = cos(rad);
    return (matrix);
}

t_shearing *create_shearing(void)
{
    t_shearing *shearing;

    shearing = malloc(sizeof(t_shearing));
    if (!shearing)
        return (NULL);
   ft_memset(shearing, 0, sizeof(t_shearing));
    return (shearing);
}

t_matrix *shearing(t_shearing *nums)
{
    t_matrix *matrix;

    if (!nums)
        return (NULL);
    matrix = create_matrix(4, 4, NULL);
    if (!matrix)
        return (NULL);
    matrix->data[0][0] = 1;
    matrix->data[1][1] = 1;
    matrix->data[2][2] = 1;
    matrix->data[3][3] = 1;
    matrix->data[0][1] = nums->xy;
    matrix->data[0][2] = nums->xz;
    matrix->data[1][0] = nums->yx;
    matrix->data[1][2] = nums->yz;
    matrix->data[2][0] = nums->zx;
    matrix->data[2][1] = nums->zy;

    return (matrix);
}

t_ray * create_ray(t_tuple *origin, t_tuple *direction)
{
    t_ray *ray;
    
    if (!origin || !direction)
        return (NULL);
    ray = malloc(sizeof (t_ray));
    if(!ray)
        return (NULL);
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

t_tuple * ray_position(t_ray *ray, double t)
{
    t_tuple *pose;
    t_tuple *a_move;

    if (!ray || !ray->direction || !ray->origin)
        return (NULL);
    a_move = mul_tuple(ray->direction, t);
    if (!a_move)
        return (NULL);
    pose = add_tuple(ray->origin, a_move);
    free(a_move);
    return (pose);
}

void free_ray(t_ray *ray)
{
    if (!ray)
        return;
    if (ray->origin)
        free(ray->origin);
    if (ray->direction)
        free(ray->direction);
    free(ray);
}

t_xs *create_intersect(int count)
{
    t_xs *xs;
    
    xs = malloc (sizeof(t_xs));
    if (!xs)
        return (NULL);
    if (count)
    {
        xs->inters = malloc(sizeof(t_intersect) * count);
        if (!xs->inters)
            return (free(xs), NULL);
    }
    xs->count = count;
    return (xs);
}

void add_intersect(t_xs **xs, t_xs *x)
{
    t_xs *tmp;
    int i, k, j, diff;

    if (!xs || !x)
        return;

    if (!*xs)
        *xs = create_intersect(x->count);
    else
        (*xs)->count += x->count;

    if (!*xs) // Check if allocation failed
        return;

    tmp = create_intersect((*xs)->count);
    if (!tmp) 
        return;

    i = 0;
    k = 0;
    j = 0;
    diff = (*xs)->count - x->count;

    while (i < diff && j < x->count)
    {
        if ((*xs)->inters[i].t < x->inters[j].t)
            tmp->inters[k++] = (*xs)->inters[i++];
        else
            tmp->inters[k++] = x->inters[j++];
    }
    while (i < diff)
        tmp->inters[k++] = (*xs)->inters[i++];
    while (j < x->count)
        tmp->inters[k++] = x->inters[j++];

    free((*xs)->inters); // Free old memory before reassigning
    (*xs)->inters = tmp->inters;
    free(tmp); // Avoid use-after-free by NOT freeing tmp->inters
}


t_intersect *intersection(double t, t_object *object)
{
    t_intersect *res;
    
    if (!object || !object->shape)
        return (NULL);
    res = malloc(sizeof(t_intersect));
    if (!res)
        return (NULL);
    res->object = object;
    res->t = t;
    return (res);
}

t_sphere *create_sphere(void)
{
    t_sphere *sphere;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);
    sphere->pos = create_point(0, 0, 0);
    if (!sphere->pos)
        return (free(sphere), NULL);
    sphere->diameter = 1 / 2;
    return (sphere);
}

t_plane *create_plane(void)
{
    t_plane *plane;

    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (NULL);
    return (plane);
}

t_cylinder *create_cylinder(void)
{
    t_cylinder *cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return (NULL);
    cylinder->center = create_point(0, 0, 0);
    if (!cylinder->center)
        return (free(cylinder), NULL);
    return (cylinder);
}

t_shape *create_shape(e_type type)
{
    t_shape *shape;

    shape = malloc(sizeof(t_shape));
    if (!shape)
        return (NULL);
    if (type == SPHERE)
    {
        shape->sphere = create_sphere();
        if (!shape)
            return (NULL);
    }
    else if (type == PLANE)
    {
        shape->plane = create_plane();
        if (!shape)
            return (NULL);
    }
    else if (type == CYLINDER)
    {
        shape->cylinder = create_cylinder();
        if (!shape)
            return (NULL);
    }
    return (shape);
}

void free_shape(t_object *object)
{
    if (!object || !object->shape)
        return;
    if (object->type == SPHERE)
    {
        free(object->shape->sphere->pos);
        free(object->shape->sphere);
    }
    else if (object->type == PLANE)
    {
        free(object->shape->plane);
    }
    else if (object->type == CYLINDER)
    {
        free(object->shape->cylinder);
    }
    free(object->shape);
}

t_object *create_object(e_type type)
{
    t_object *object;
    
    object = NULL;
    object = malloc(sizeof(t_object));
    if (!object)
        return (NULL);
    object->shape = create_shape(type);
    if (!object->shape)
        return (free(object), NULL);
    object->transform = identity_matrix();
    if (!object->transform)
        return (free_shape(object), free(object),NULL);
    object->material = create_material();
    if (!object->material)
        return (free_matrix(object->transform), free_shape(object) ,free(object), NULL);
    object->type = type;
    return (object);
}

void print_intersects(t_xs *xs)
{
    t_intersect *tmp;
    int i;

    if (!xs)
        return;
    i = -1;
    tmp = xs->inters;
    if (xs->count != 1)
    while (++i < xs->count)
        printf("Object : %p, xs.t : %f\n",tmp[i].object ,tmp[i].t);
}

double hit(t_xs *xs) // return a positive num if there is intersction accure , otherwise return negative number
{
    double old;
    int i;

    if (!xs)
        return (-1);
    i = -1;
    while (++i < xs->count)
    {
        if (xs->inters[i].t > 0 )
            return (xs->inters[i].t);
    }
    return (-1);
}

t_ray *transform(t_ray *ray, t_matrix *matrix)
{
    t_ray *res;
    t_tuple *orgin;
    t_tuple *dir;

    if (!ray || !matrix)
        return (NULL);
    res = create_ray(orgin, dir);
    res->direction =  matrix_tuple_mul4x4(matrix, ray->direction);
    res->origin = matrix_tuple_mul4x4(matrix, ray->origin);
    return (res);
}

int  set_transform(t_object **object, t_matrix *matrix)
{
    if (!object || !*object || !(*object)->transform || !matrix)
        return (-1);
    free((*object)->transform);
    (*object)->transform = matrix;
    return (0);
}

t_tuple *sphere_local_normal_at(t_tuple *local_point)
{
    return (create_vector(local_point->x, local_point->y, local_point->z));
}

t_tuple *plane_local_normal_at(void)
{
    // The plane's normal is always (0, 1, 0) in local space.
    return (create_vector(0, 1, 0));
}

t_tuple *cylander_local_normal_at(t_tuple *local_point)
{
    return (create_vector(local_point->x, 0, local_point->z));
}

t_tuple *local_normal_at (t_object *object, t_tuple *local_point)
{
    if (object->type == SPHERE)
        return (sphere_local_normal_at(local_point));
    else if (object->type == PLANE)
        return (plane_local_normal_at());
    else if (object->type == CYLINDER)
        return (cylander_local_normal_at(local_point));
    return (NULL);
}

int transformations(t_object *object, t_tuple *point, t_matrix **inverse, t_tuple **local_normal)
{
    t_tuple *local_point;

    *inverse = matrix_inverse(object->transform);
    if (!*inverse)
        return (-1);
    local_point = matrix_tuple_mul4x4(*inverse, point);
    if (!local_point)
        return(-1);
    *local_normal = local_normal_at(object, local_point);
    if (!*local_normal)
        return (free(local_point), -1);
    return (free(local_point), 0);
}
int normal_calculations(t_matrix *inverse, t_tuple *local_normal, t_tuple **world_normal)
{
    t_matrix *transpose;

    transpose = matrix_transpose4x4(inverse);
    if (!transpose)
       return (free(local_normal),free_matrix(inverse), -1);
    *world_normal = matrix_tuple_mul4x4(transpose, local_normal);
    if (!*world_normal)
        return (free_matrix(transpose) ,free(local_normal),free_matrix(inverse), -1);
    (*world_normal)->w = 0;
    return (free_matrix(transpose) ,free(local_normal),free_matrix(inverse), 0);
}

t_tuple * normal_at(t_object *object, t_tuple *point)
{
    t_matrix *inverse;
    t_tuple *local_normal;
    t_tuple *world_normal;
    t_tuple *res;

    if (!object || !object->shape || !object->transform || !object->material || !point)
        return (NULL);
    if (transformations(object, point, &inverse, &local_normal))
           return (NULL); // TO DO free and exit()
    if (normal_calculations(inverse, local_normal, &world_normal))
        return (NULL); // TO DO free and exit()
    res = norm_tuple(world_normal);
    return (free(world_normal), res);
}

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
    t_tuple *mul;
    t_tuple *mul1;
    t_tuple *sub;

    mul = mul_tuple(normal, 2);
    mul1 = mul_tuple(mul, dot_tuple(in, normal));
    sub = sub_tuple(in, mul1);
    free(mul);
    free(mul1);
    return (sub);
}

t_light *point_light(double brightness, t_tuple *position, t_tuple *color)
{
    t_light *light;

    light = malloc(sizeof(t_light));
    if (!light)
        return (NULL);
    light->brightness = brightness;
    light->position = position;
    light->color = color;
    light->intensity = mul_tuple(color, brightness);
    if (!light->intensity)
        return (free(light), NULL);
    return (light);
}

t_material *create_material(void)
{
    t_material *mat;

    mat = malloc(sizeof(t_material));
    if (!mat)
        return (NULL);
    mat->color = create_color(1, 1, 1); // from file
    if (!mat->color)
        return (free(mat), NULL);
    mat->ambient = 0.1; // from file
    mat->diffuse = 0.9;
    mat->specular = 0.9;
    mat->shininess = 200.0;
    return (mat);
}

void set_color_material(t_material *m, t_tuple *color)
{
    if (!m)
        return;
    free (m->color);
    m->color = color;
}

// TESTS

t_tuple *lighting(t_material *material, t_light *light, t_tuple *point, t_tuple *eyev, t_tuple *normalv, bool in_shadow)
{
    t_tuple *res;
    t_tuple *effective_color;
    t_tuple *lightv;
    t_tuple *ambient;
    t_tuple *diffuse;
    t_tuple *specular;
    t_tuple *reflectv;
    t_tuple *tmp;
    double light_dot_normal;
    double reflect_dot_eye;
    double factor;

    // print adresees
    // printf("material clr : %p , light int %p\n", material->color, light->intensity);
    // exit(1);
    effective_color = hadamard_product(material->color, light->intensity);
    lightv = norm_tuple(sub_tuple(light->position, point));

    // Ambient should always be computed
    ambient = mul_tuple(effective_color, material->ambient);

    if (in_shadow)
        return ambient;  // Only return ambient when in shadow

    light_dot_normal = dot_tuple(lightv, normalv);
    if (light_dot_normal < 0)
    {
        diffuse = create_color(0, 0, 0);
        specular = create_color(0, 0, 0);
    }
    else
    {
        diffuse = mul_tuple(effective_color ,material->diffuse * light_dot_normal);
        reflectv = reflect(mul_tuple(lightv, -1), normalv);
        reflect_dot_eye =  dot_tuple(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = create_color(0, 0, 0);
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);
            specular = mul_tuple(light->intensity , material->specular * factor);
        }
    }

    tmp = add_tuple(ambient , add_tuple(diffuse ,specular));
    return create_color(tmp->x, tmp->y, tmp->z);
}

// WORLD 

t_world *create_world(void)
{
    t_world *world;

    world = malloc(sizeof(t_world));
    if (!world)
        return (NULL);
    world->lights_list = NULL;
    world->objects_list = NULL;
    return (world);
}

t_world *default_world(void)
{
    t_world *world;
    t_light *light;
    t_object *object1;
    t_object *object2;
    t_list *light_list;
    t_list *objects_list;
    t_tuple *point;
    t_tuple *color;
    t_material *m;
    t_tuple *c;

    light_list = NULL;
    objects_list = NULL;
    world = create_world();
    if (!world)
        return (NULL);
    point = create_point(-10, 10, -10);
    color = create_color(1, 1, 1);
    light = point_light(0.6 ,point, color);
    object1 = create_object(SPHERE);
    c = create_color(0.8, 1.0, 0.6);
    set_color_material(object1->material, c);
    object1->material->specular = 0.2;
    object1->material->diffuse = 0.7;
    object2 = create_object(SPHERE);
    set_transform(&object2, scaling(0.5, 0.5, 0.5));
    ft_lstadd_back(&light_list, ft_lstnew(light));
    ft_lstadd_back(&objects_list, ft_lstnew(object1));
    ft_lstadd_back(&objects_list, ft_lstnew(object2));
    world->lights_list = light_list;
    world->objects_list = objects_list;

    return (world);
}


t_xs *intersect_world(t_world *world, t_ray *ray)
{
    t_xs *xs;
    t_xs *x;
    t_object *object;
    t_list *lst;
    int i;

    i = 0;
    xs = NULL;
    lst = world->objects_list;
    while (lst)
    {
        x = intersect(lst->content, ray);
        add_intersect(&xs, x);
        i++;
        lst = lst->next;
    }
    return (xs);
    
}

t_comps *prepare_computations(t_intersect *x, t_ray *ray)
{
    t_comps *comps;
    t_tuple *mul;

    comps = malloc(sizeof(t_comps));
    if (!comps)
        return (NULL);
    comps->t = x->t;
    comps->object = x->object;
    comps->point = ray_position(ray, comps->t);
    comps->eyev = mul_tuple(ray->direction, -1);
    comps->normalv = normal_at(comps->object, comps->point);
    if (dot_tuple(comps->normalv, comps->eyev) < 0)
    {
        comps->inside = true;
        comps->normalv = mul_tuple(comps->normalv, -1);
    }
    else
        comps->inside = false;
    mul = mul_tuple(comps->normalv, EPSILON);
    comps->over_point  = add_tuple(comps->point, mul);
    free(mul);
    return(comps);
}

t_tuple *shade_hit(t_world *world, t_comps *comps) // return a color
{
    t_tuple *color;
    t_tuple *new_res;
    t_tuple *res;
    t_tuple *n_res;
    t_list *lst;
    bool shadowed;
    int i;
    
    i = 0;
    res = create_color(0, 0, 0);
    shadowed = is_shadowed(world, comps->over_point);

    lst = world->lights_list;
    while (lst)
    {
        color = lighting(comps->object->material, world->lights_list->content,
        comps->point, comps->eyev, comps->normalv, shadowed);
        new_res = add_tuple(res, color);
        free(res);
        free(color);
        res = new_res;
        lst = lst->next;
        i++;
    
    }
    if (i > 0)
    {
        n_res = mul_tuple(res, 1.0 / i);
        free(res);
        res = n_res;
    }
    return (res);
}

t_intersect *get_first_positive(t_xs *xs)
{
    t_intersect *res;
    int i;

    i = 0;
    res = NULL;
    while (i < xs->count)
    {
        if (xs->inters[i].t > 0)
        {
            res = xs->inters + i;
            break;
        }
        i++;
    }
    return (res);
}

t_tuple *color_at(t_world *w, t_ray *r)
{
    t_xs *xs;
    t_comps *comps;
    t_intersect *first_inter;
    
    xs = intersect_world(w, r);
    first_inter = get_first_positive(xs);
    if (!first_inter)
        return (create_color(0, 0, 0));
    comps = prepare_computations(first_inter, r);
    return (shade_hit(w, comps));
}

t_matrix *view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
    t_matrix *res;
    t_tuple *forword;
    t_tuple *sub;
    t_tuple *upn;
    t_tuple *left;
    t_tuple *true_up;
    t_matrix *trans;
    t_matrix *orientation;
    double **arr;

    sub = sub_tuple(to, from);
    forword = norm_tuple(sub);
    upn = norm_tuple(up);
    left = cross_tuple(forword, upn);
    true_up = cross_tuple(left, forword);
    arr = create_arr(4, 4);
    arr[0][0] = left->x;
    arr[0][1] = left->y;
    arr[0][2] = left->z;
    arr[1][0] = true_up->x;
    arr[1][1] = true_up->y;
    arr[1][2] = true_up->z;
    arr[2][0] = -forword->x;
    arr[2][1] = -forword->y;
    arr[2][2] = -forword->z;
    arr[3][3] = 1;
    orientation = create_matrix(4, 4, (const double **)arr);
    trans = translation(-from->x, -from->y, -from->z);
    res = matrix_multiply(orientation, trans, 4);

    return (res);
}

t_matrix *identity_matrix(void)
{
    t_matrix *identity_matrix;
    
    identity_matrix = create_matrix(4, 4, NULL);
    identity_matrix->data[0][0] = 1;
    identity_matrix->data[1][1] = 1;
    identity_matrix->data[2][2] = 1;
    identity_matrix->data[3][3] = 1;
    return (identity_matrix);
}

void pixel_size_cal(t_camera *cam)
{
    double half_view;
    double aspect;

    half_view = tan(cam->field_of_view / 2);
    aspect = (double)(cam->hsize) / cam->vsize;
    
    if (aspect >= 1)
    {
        cam->half_width = half_view;
        cam->half_height = half_view / aspect;
    }
    else
    {
        cam->half_width = half_view * aspect;
        cam->half_height = half_view;
    }
    cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

t_camera *create_camera(int hsize, int vsize, double field_of_view_rad)
{
    t_camera *cam;

    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (NULL);
    cam->field_of_view = field_of_view_rad;
    cam->hsize = hsize;
    cam->vsize = vsize;
    cam->transform = identity_matrix();
    pixel_size_cal(cam);
    cam->pos = create_point(0, 0, 0);
    cam->direction = create_vector(0, 0, 0);
    return (cam);
}
t_ray *ray_for_pixel(t_camera *cam, t_matrix *inverse, t_tuple *origin, int px, int py)
{
    double xoffset; 
    double yoffset;
    double world_x;
    double world_y;
    t_tuple *pixel;
    t_tuple *direction; 
    
    xoffset = (px + 0.5) * cam->pixel_size;
    yoffset = (py + 0.5) * cam->pixel_size;
    world_x = cam->half_width - xoffset;
    world_y = cam->half_height - yoffset;
    pixel = matrix_tuple_mul4x4(inverse, create_point(world_x, world_y, -1));
    direction = norm_tuple(sub_tuple(pixel, origin));
    return (create_ray(origin, direction));
}

 t_canvas *render(t_camera *cam, t_world *world, void *mlx, void *win)
{
    t_canvas *image;
    t_tuple *color;
    t_ray *ray;
    t_tuple *origin;
    t_matrix *inverse;

    int x;
    int y;
    inverse = matrix_inverse(cam->transform);
    if (!matrix_invertiblity(cam->transform))
        printf("NOT AN ERROR ,BUT YOU MAY NOT SEE A THING !\n");
    origin = matrix_tuple_mul4x4(inverse, create_point(0 ,0 ,0));
    image = create_canvas(cam->hsize, cam->vsize, mlx);
    y = 0;
    while(y < cam->vsize - 1)
    {
        x = 0;
        while (x < cam->hsize - 1)
        {
            ray = ray_for_pixel(cam ,inverse, origin,x, y);
            color = color_at(world, ray);
            write_pixel(image, x, y, color);
            // mlx_pixel_put(mlx, win, x, y, color_to_int(color));
            x++;
        }
        y++;
    }
    return (image);   
}


// MAIN -----------------------------------------------------------------------
void render_scene(void)
{

    t_canvas *can;
    t_world *world;
    t_camera *cam;
    void *mlx;
    void *win;

    // Initialize MiniLibX
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");

    // Create Camera
    cam = create_camera(WIDTH, HEIGHT, M_PI/ 3);
    cam->transform = view_transform(create_point(0, 15, -20), create_point(0, 1, 0), create_vector(0, 1, 0));

    // Create World
    world = create_world();
    world->lights_list = ft_lstnew(point_light(0.5, create_point(-10, 10, -10), create_color(1, 1, 1)));

    // Create Floor
    t_object *floor = create_object(PLANE);
    floor->transform = matrix_multiply(
        translation(0, 0, 0),
        scaling(10, 0.01, 10), 4
    );
    floor->material = create_material();
    floor->material->color = create_color(1, 0.9, 0.9);
    floor->material->specular = 0;

    // // Create Left Wall
    // t_object *left_wall = create_object(SPHERE);
    // left_wall->transform = matrix_multiply(
    //     translation(0, 0, 5),
    //     matrix_multiply(
    //         rotation_y(-M_PI/ 4),
    //         matrix_multiply(
    //             rotation_x(M_PI/ 2),
    //             scaling(10, 0.01, 10), 4
    //         ), 4
    //     ), 4
    // );
    // left_wall->material = floor->material;

    // // Create Right Wall
    // t_object *right_wall = create_object(SPHERE);
    // right_wall->transform = 
    //  matrix_multiply (translation(0, 0, 5),
    //  matrix_multiply(rotation_y(M_PI/ 4), 
    //  matrix_multiply(rotation_x(M_PI/ 2),scaling(10, 0.01, 10), 4), 4), 4 );
    // right_wall->material = floor->material;

    // Create Middle Sphere
    // t_object *middle = create_object(CYLINDER);
    // middle->transform = translation(-0.5, 1, 0.5);
    // middle->material = create_material();
    // middle->material->color = create_color(0.1, 1, 0.5);
    // middle->material->diffuse = 0.7;
    // middle->material->specular = 0.3;

    // // Create Right Sphere
    // t_object *right = create_object(SPHERE);
    // right->transform = matrix_multiply(
    //     translation(1.5, 0.5, -0.5),
    //     scaling(0.5, 0.5, 0.5), 4
    // );
    // right->material = create_material();
    // right->material->color = create_color(0.5, 1, 0.1);
    // right->material->diffuse = 0.7;
    // right->material->specular = 0.3;

    // // Create Left Sphere
    // t_object *left = create_object(SPHERE);
    // left->transform = matrix_multiply(
    //     translation(-1.5, 0.33, -0.75),
    //     scaling(0.33, 0.33, 0.33), 4
    // );
    // left->material = create_material();
    // left->material->color = create_color(1, 0.8, 0.1);
    // left->material->diffuse = 0.7;
    // left->material->specular = 0.3;

    // // Add objects to the world
    // t_list *objects = NULL;
    // ft_lstadd_front(&objects, ft_lstnew(floor));
    // // ft_lstadd_front(&objects, ft_lstnew(left_wall));
    // // ft_lstadd_front(&objects, ft_lstnew(right_wall));
    // ft_lstadd_front(&objects, ft_lstnew(middle));
    // ft_lstadd_front(&objects, ft_lstnew(right));
    // ft_lstadd_front(&objects, ft_lstnew(left));
    // world->objects_list = objects;

    // Render the scene
    can = render(scene()->camera, scene(), mlx, win);
    mlx_put_image_to_window(mlx, win, can->img->img, 0, 0);
    printf("Rendering done\n");
    mlx_loop(mlx);
}



bool is_shadowed(t_world *world, t_tuple *point)
{
    t_tuple *v;
    t_tuple *direction;
    t_ray *r;
    t_xs *intersects;
    double distance;
    double h;

    v = sub_tuple(((t_light *)(world->lights_list->content))->position, point);
    distance = len_tuple(v);
    direction = norm_tuple(v);
    r = create_ray(point, direction);
    intersects = intersect_world(world, r);
    h = hit(intersects);
    if (h > 0 && h < distance)
        return (true);
    else
        return (false);
}

void print_material(t_material *m)
{
    print_type(m->color);
    printf("ambient :%f, diffuse: %f, shininess: %f, specular :%f\n",m->ambient, m->diffuse, m->shininess, m->specular);
}

int prepare_xs(t_xs **xs, t_object *object, double t1, double t2)
{
    *xs = create_intersect(2);
    if (!*xs)
        return (-1); // TO DO free all world and exit
    (*xs)->count = 2;
    (*xs)->inters[0].t = fmin(t1, t2);
    (*xs)->inters[1].t = fmax(t1, t2);
    // if (t1 > t2)
    // {
    //     (*xs)->inters[0].t = t2;
    //     (*xs)->inters[1].t = t1;
    // }
    // else
    // {
    //     (*xs)->inters[0].t = t1;
    //     (*xs)->inters[1].t = t2;
    // }
    (*xs)->inters[0].object = object;
    (*xs)->inters[1].object = object;
    return (0);
}
int sphere_calcule(t_object *object, t_ray *ray ,t_tuple *four)
{
    t_matrix *inverse;
    t_ray *ray2;
    t_tuple *t_sphereo_ray;

    inverse = matrix_inverse(object->transform);
    if (!inverse)
        return (-1);
    ray2 = transform(ray, inverse);
    if (!ray2)
        return (free_matrix(inverse), -1);
    t_sphereo_ray = sub_tuple(ray2->origin, object->shape->sphere->pos);
    if (!t_sphereo_ray)
        return (free_ray(ray2), free_matrix(inverse), -1);
    four->x = dot_tuple(ray2->direction, ray2->direction);
    four->y = 2 * dot_tuple(ray2->direction, t_sphereo_ray);
    four->z = dot_tuple(t_sphereo_ray, t_sphereo_ray) - 1;
    four->w = (four->y * four->y) - (4 * four->x * four->z);
    if (four->w < 0)
        return (free(t_sphereo_ray), free_ray(ray2), free_matrix(inverse), 1);
    return (free(t_sphereo_ray), free_ray(ray2), free_matrix(inverse), 0);
}

double sphere_helper(t_object *object, t_ray *ray, double *t1, double *t2) // 1 : NOT HITTED, 0 : HITTED, -1 : ERROR
{     
    t_tuple *four;
    double dis;

    four = create_tuple(0, 0, 0, 0);
    if (!four)
        return (-1);
    dis = sphere_calcule(object, ray ,four);
    if (dis == 1)
        return (free(four), 1); // SPHERE NOT HITTED
    else if (dis == -1)
        return (free(four), -1); // ERROR
    *t1 = (-four->y - sqrt(four->w)) / (2 * four->x);
    *t2 = (-four->y + sqrt(four->w)) / (2 * four->x);
    free(four);
    return (0);
}

t_xs *sphere_intersect(t_object *object, t_ray *ray)
{
    t_xs *xs;       
    double t1;
    double t2;
    double check;

    check = sphere_helper(object, ray, &t1, &t2);
    if (check == -1)
        return (NULL); // TO DO free all world and exit()
    else if (check == 1)
        return (NULL); // FREE AND RETURN NULL , NOT ERROR JUST SPHERE NOT HITTED SO NO EXIT()
    if (prepare_xs(&xs, object, t1, t2))
        return (NULL); // TO DO free all world and exit()
    return (xs);
}

t_xs *plane_intersect(t_object *object, t_ray *ray)
{
    t_xs *xs;

    xs = create_intersect(1);
    if (!xs)
        return (NULL); // TO DO free all world and exit()
    if (fabs(ray->direction->y) < EPSILON)
        return (NULL); // NO EXIT
    xs->count = 1;
    xs->inters->object = object;
    xs->inters->t = -ray->origin->y / ray->direction->y;
    return (xs);
}

t_xs *cylander_intersect(t_object *object, t_ray *ray)
{
    t_xs *xs;
    t_tuple *four;
    double t1;
    double t2;

    four = create_tuple(0, 0, 0, 0);
    if (!four)
        return (NULL);
    four->x = (ray->direction->x * ray->direction->x) + (ray->direction->z * ray->direction->z);
    if (four->x < EPSILON)
        return (free(four), NULL);
    four->y = (2 * ray->origin->x * ray->direction->x) + (2 * ray->origin->z * ray->direction->z);
    four->z = (ray->origin->x * ray->origin->x) + (ray->origin->z * ray->origin->z) - 1;
    four->w = (four->y * four->y) - (4 * four->x * four->z);
    if (four->w < 0)
        return (free(four), NULL);
    t1 = (-four->y - sqrt(four->w)) / (2 * four->x);
    t2 = (-four->y + sqrt(four->w)) / (2 * four->x);
    if (prepare_xs(&xs, object, t1, t2))
        return (NULL); // TO DO free all world and exit()
    return (xs);
}

t_xs *intersect_object(t_object *object, t_ray *ray)
{
    if (object->type == SPHERE)
        return (sphere_intersect(object, ray));
    else if (object->type == PLANE)
        return (plane_intersect(object, ray));
    else if (object->type == CYLINDER)
        return (cylander_intersect(object, ray));
    return (NULL);
}

t_xs *intersect(t_object *object, t_ray *ray)
{
    t_ray *local_ray;
    t_matrix *inverse;

    if (!object || !object->material || !object->shape || !object->transform)
        return (NULL);
    inverse = matrix_inverse(object->transform);
    local_ray = transform(ray, inverse);
    free_matrix(inverse); // Free the inverse matrix
    return (intersect_object(object, ray));
}
void print_ray(t_ray *ray)
{
    print_type(ray->origin);
    print_type(ray->direction);
}

void print_map_data(void)
{
    /*
        t_camera                *camera;
        t_list                  *lights_list;
        t_list                  *objects_list;
        t_list                  *ambient_list;
    */
    t_list *lights_list;
    t_list *objects_list;
    t_list *ambient_list;
    t_object *object;
    t_world *world = scene();
    
    lights_list = world->lights_list;
    objects_list = world->objects_list;
    ambient_list = world->ambient_list;
    printf("CAMERA\n");
    print_type(world->camera->pos);
    print_type(world->camera->direction);
    printf("%f\n", world->camera->field_of_view);
    printf("LIGHTS\n");
    while (lights_list)
    {
        print_type(((t_light *)lights_list->content)->position);
        print_type(((t_light *)lights_list->content)->color);
        printf("%f\n", ((t_light *)lights_list->content)->brightness);
        
        lights_list = lights_list->next;
    }
    printf("OBJECTS\n");
    while (objects_list)
    {
        object = objects_list->content;
        if (object->type == SPHERE)
        {
            printf("SPHERE\n");
            print_type(object->shape->sphere->pos);
            printf("Diameter : %f\n", object->shape->sphere->diameter);
        }
        else if (object->type == PLANE)
        {
            printf("PLANE\n");
            /*
                t_tuple   *pos; // center
                t_tuple   *normal; // [-1, 1] [-1, 1] [-1, 1]
                t_tuple   *color;
            */
            print_type(object->shape->plane->pos);
            print_type(object->shape->plane->normal);
            
        }
        else if (object->type == CYLINDER)
        {
            printf("CYLINDER\n");
            print_type(object->shape->cylinder->center);
        }
        print_material(object->material);
        objects_list = objects_list->next;
    }
    printf("AMBIENT\n");
    while (ambient_list)
    {
        print_type(((t_ambient *)ambient_list->content)->color);
        printf("%f\n", ((t_ambient *)ambient_list->content)->lighting_ratio);
        ambient_list = ambient_list->next;
    }
    
    
}

int main(int ac, char **av)
{
    read_map_data(av[1]);
    print_map_data();
    render_scene();
}