/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:17:09 by baouragh          #+#    #+#             */
/*   Updated: 2025/02/05 17:21:12 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "geo.h"

// DEBUG FUNCTION-------------------------------------------------------------------------------
void print_type(t_tuple *tuple)
{
    if (!tuple)
        return (printf("ERR TUPLE NULL\n"), (void)0);
    if (tuple->w == 0)
        printf("is Vector : x = %f, y = %f, z = %f, w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else if (tuple->w == 1)
        printf("is Point : x = %f, y = %f, z = %f , w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else if (tuple->w == 20)
        printf("is Color : x = %f, y = %f, z = %f , w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else
        printf("is Undefined : x = %f, y = %f, z = %f , w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
}

// CREATE A TUPLE STRUCTURE---------------------------------------------------------------------
t_tuple *create_tuple(double x, double y, double z, double w, t_list **garbge)
{
    t_tuple *tuple;

    tuple = safe_malloc(sizeof(t_tuple), garbge);
    tuple->x = x;
    tuple->y = y;
    tuple->z = z;
    tuple->w = w;
    return (tuple);
}

t_tuple *create_point(double x, double y, double z, t_list **garbge)
{
    return (create_tuple(x, y, z, 1, garbge));
}

t_tuple *create_vector(double x, double y, double z, t_list **garbge)
{
    return (create_tuple(x, y, z, 0, garbge));
}

t_tuple *create_color(double x, double y, double z, t_list **garbge)
{
    return (create_tuple(x, y, z, 20, garbge));
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

t_tuple *add_tuple(t_tuple *a, t_tuple *b, t_list **garbge)
{
    return (create_tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w, garbge));
}

t_tuple *sub_tuple(t_tuple *a, t_tuple *b, t_list **garbge)
{
    return (create_tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w, garbge));
}

t_tuple *negate_tuple(t_tuple *a, t_list **garbge)
{
    return (create_tuple(-a->x, -a->y, -a->z, -a->w, garbge));
}

t_tuple *mul_tuple(t_tuple *a, double b, t_list **garbge)
{
    return (create_tuple(a->x * b, a->y * b, a->z * b, a->w * b, garbge));
}

t_tuple *div_tuple(t_tuple *a, double b, t_list **garbge)
{
    return (create_tuple(a->x / b, a->y / b, a->z / b, a->w / b, garbge));
}
double len_tuple(t_tuple *a)
{
    return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}
t_tuple *norm_tuple(t_tuple *a, t_list **garbge)
{
    return (div_tuple(a, len_tuple(a), garbge));
}

double dot_tuple(t_tuple *a, t_tuple *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_tuple *cross_tuple(t_tuple *a, t_tuple *b, t_list **garbge)
{
    return (create_vector(a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x, garbge));
}

t_tuple *hadamard_product(t_tuple *a, t_tuple *b, t_list **garbge)
{
    return (create_color(a->x * b->x, a->y * b->y, a->z * b->z, garbge));
}

// PROJECTILE FUNCS--------------------------------------------------------------------------

t_projectile *create_projectile(t_tuple *position, t_tuple *speed, t_list **garbge)
{
    t_projectile *projectile;
    
    projectile = safe_malloc(sizeof(t_projectile), garbge);
    projectile->position = position;
    projectile->speed = speed;
    return (projectile);
}

t_environment *create_environment(t_tuple *gravity, t_tuple *wind,  t_list **garbge)
{
    t_environment *environment;

    environment = safe_malloc(sizeof(t_environment), garbge);
    environment->gravity = gravity;
    environment->wind = wind;
    return (environment);
}

t_projectile *tick(t_environment *env, t_projectile *projectile,  t_list **garbge)
{
    t_tuple *position;
    t_tuple *speed;

    position= add_tuple(projectile->position, projectile->speed, garbge);
    speed = add_tuple(add_tuple(projectile->speed, env->gravity, garbge), env->wind, garbge);

    return (create_projectile(position, speed, garbge));
}

// MLX MY--------------------------------------------------------------------------------------

void add_to_garbge(t_list **garbge, void *adress)
{
    t_list *node;
    
    node = ft_lstnew(adress);
    if (!node)
    {
        ft_lstclear(garbge, free);
        exit(1);
    }
    ft_lstadd_front(garbge, node);
}

void *safe_malloc(size_t size, t_list **garbge)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        ft_lstclear(garbge, free);
        exit(20);
    }
    add_to_garbge(garbge, ptr);
    return (ptr);
}


t_img *new_img( int width, int height, void *mlx, t_list **garbge)
{
    t_img *img;
    t_list *node;

    img = safe_malloc(sizeof(t_img), garbge);
    img->img = mlx_new_image(mlx, width, height);
    if (!img->img)
        return (ft_lstclear(garbge, free), NULL);
    node = ft_lstnew(img->img);
    if (!node)
        return (ft_lstclear(garbge, free), NULL);
    ft_lstadd_front(garbge, node);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    if (!img->addr)
        return (ft_lstclear(garbge, free), NULL);
    node = ft_lstnew(img->addr);
    if (!node)
        return (ft_lstclear(garbge, free), NULL);
    ft_lstadd_front(garbge, node);
    return (img);
}

t_canvas * create_canvas(int width , int height, void *mlx_ptr, t_list **garbge)
{
    t_canvas *canvas;

    if (!mlx_ptr)
        return (NULL);
    canvas = safe_malloc(sizeof(t_canvas), garbge);
    canvas->mlx = mlx_ptr;
    canvas->width = width;
    canvas->height = height;
    canvas->img = new_img(width, height, mlx_ptr, garbge);
    return (canvas);
}

int color_at (t_img *img, int x, int y)
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

    return ((r << 16) | (g << 8) | (b));
}

t_tuple * int_to_color(int color, t_list **garbge)
{
    double r;
    double g;
    double b;

    r = ((color >> 16) & 0XFF) / 255.0;
    g = ((color >> 8) & 0XFF) / 255.0;
    b = (color & 0XFF) / 255.0;

    return (create_color(r, g, b, garbge));
}

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color)
{
    my_mlx_pixel_put(canvas->img, x, y, color_to_int(color));
}

t_tuple *pixel_at(t_canvas *canvas, int x, int y, t_list **garbge)
{ 
    int color;

    color = color_at(canvas->img, x, y);
    return (int_to_color(color, garbge));
}

// MATRIXS INTO THE SCENE------------------------------------------------------------

void free_arr(double **res, int i)
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

double **create_arr(int rows, int cols, t_list **garbge)
{
    double **res;
    int i;

    res = safe_malloc(sizeof(double *) * rows, garbge);
    i = -1;
    while (++i < cols)
        res[i] = safe_malloc(sizeof(double) * cols, garbge);
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

double **set_zeros(int rows, int colums, t_list **garbge)
{
    int i;
    int j;
    double **res;

    if (rows <= 0 || colums <= 0)
        return (NULL);
    res = safe_malloc(rows * sizeof(double *), garbge);
    i = 0;
    while (i < rows)
    {
        res[i] = safe_malloc(colums * sizeof(double), garbge);
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

double **duplicate_array(int rows, int colums, const double **arr, t_list **garbge)
{
    int i;
    int j;
    double **res;

    if (!arr || !*arr || rows <= 0 || colums <= 0)
        return (NULL);
    res = safe_malloc(rows * sizeof(double *), garbge);
    i = 0;
    while (i < rows)
    {
        res[i] = safe_malloc(colums * sizeof(double), garbge);
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

t_matrix *create_matrix(int rows, int colums, const double **arr, t_list **garbge)
{
    t_matrix *matrix;

    if (rows <= 0 || colums <= 0 || rows != colums)
        return (NULL);
    matrix = safe_malloc(sizeof(t_matrix), garbge);
    matrix->size = rows;
    if (!arr || !*arr)
    {
        matrix->data = set_zeros(rows, colums, garbge);
        return (matrix);
    }
    matrix->data = duplicate_array(rows, colums, arr, garbge);
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

t_matrix *matrix_multiply(t_matrix *a, t_matrix *b, int size, t_list **garbge) // JUST FOR 4X4 matrixs 
{
    t_matrix *matrix;
    int i;
    int j;

    if (!a || !b || !a->data || !b->data || a->size != size || b->size != size)
        return (0);
    matrix = create_matrix(size, size, NULL, garbge);
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

t_tuple *matrix_tuple_mul4x4(t_matrix *a, t_tuple *t, t_list **garbge) // JUST FOR 4X4 matrixs 
{
    t_tuple *tuple;
    int i;
    double res;

    if (!a || !t || !a->data || a->size != 4)
        return (0);
    tuple = create_tuple(0, 0, 0, 0, garbge);
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

t_matrix *matrix_transpose4x4(t_matrix *matrix, t_list **garbge)
{
    t_matrix *trans;
    int i;
    int j;

    if (!matrix || !matrix->data)
        return (NULL);
    trans = create_matrix(4, 4 , NULL, garbge);
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

t_matrix *sub_matrix(t_matrix *matrix, int row, int column, t_list **garbge)
{
    t_matrix *submatrix;

    if (!matrix || !matrix->data || matrix->size <= column || matrix->size <= row)
        return (NULL);
    submatrix = create_matrix(matrix->size - 1, matrix->size - 1, NULL, garbge);
    remove_row_cols(matrix ,submatrix, row, column);
    return (submatrix);
}

double matrix_cofactor(t_matrix *matrix, int row, int column, t_list **garbge)
{
    double cofactor;

    cofactor = matrix_minor(matrix, row, column, garbge);
    if ((row + column) % 2)
        return (-cofactor);
    return (cofactor);
}

double matrix_determinant(t_matrix *matrix, t_list **garbge)
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
            determinant += matrix_cofactor(matrix, 0, j, garbge) * matrix->data[0][j];
    }
    return (determinant);
}

double matrix_minor(t_matrix *matrix, int row, int column, t_list **garbge)
{
    t_matrix *sub;
    double  minor;

    if (!matrix || !matrix->data)
        return (0);
    sub = sub_matrix(matrix, row, column, garbge);
    minor = matrix_determinant(sub, garbge);
    return (minor);
}

bool matrix_invertiblity(t_matrix *matrix, t_list **garbge)
{
    double determinant;

    determinant = matrix_determinant(matrix, garbge);
    return ((fabs(determinant) > EPSILON));
}

t_matrix *matrix_inverse(t_matrix *matrix, t_list **garbge)
{
    t_matrix *inverse;
    double cofactor;
    double determinant;
    int row;
    int col;

    if (!matrix || !matrix->data || !matrix_invertiblity(matrix, garbge))
        return (NULL);
    inverse = create_matrix(matrix->size, matrix->size, NULL, garbge);
    determinant = matrix_determinant(matrix, garbge);
    row = -1;
    while (++row < matrix->size)
    {
        col = -1;
        while (++col < matrix->size)
        {
            cofactor = matrix_cofactor(matrix, row, col, garbge);
            inverse->data[col][row] = cofactor / determinant;
        }
    }
    return (inverse);
}

t_matrix* translation(double x, double y, double z, t_list **garbge)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL, garbge);
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

t_matrix *scaling(double x, double y, double z, t_list **garbge)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL, garbge);
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

t_matrix *rotation_x(double rad, t_list **garbge)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL, garbge);

    matrix->data[0][0] = 1;
    matrix->data[3][3] = 1;
    
    matrix->data[1][1] = cos(rad);
    matrix->data[1][2] = -sin(rad);
    matrix->data[2][1] = sin(rad);
    matrix->data[2][2] = cos(rad);
    return (matrix);
}

t_matrix *rotation_y(double rad, t_list **garbge)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL, garbge);
    matrix->data[3][3] = 1;
    matrix->data[2][1] = 1;
    
    matrix->data[0][0] = cos(rad);
    matrix->data[0][2] = sin(rad);
    matrix->data[2][0] = -sin(rad);
    matrix->data[2][2] = cos(rad);
    return (matrix);
}

t_matrix *rotation_z(double rad, t_list **garbge)
{
    t_matrix *matrix;

    matrix = create_matrix(4, 4, NULL, garbge);

    matrix->data[3][3] = 1;
    matrix->data[2][2] = 1;
    
    matrix->data[0][0] = cos(rad);
    matrix->data[0][1] = -sin(rad);
    matrix->data[1][0] = sin(rad);
    matrix->data[1][1] = cos(rad);
    return (matrix);
}

t_shearing *create_shearing(t_list **garbge)
{
    t_shearing *shearing;

    shearing = safe_malloc(sizeof(t_shearing), garbge);
   ft_memset(shearing, 0, sizeof(t_shearing));
    return (shearing);
}

t_matrix *shearing(t_shearing *nums, t_list **garbge)
{
    t_matrix *matrix;

    if (!nums)
        return (NULL);
    matrix = create_matrix(4, 4, NULL, garbge);

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

t_ray * create_ray(t_tuple *origin, t_tuple *direction, t_list **garbge)
{
    t_ray *ray;
    
    if (!origin || !direction)
        return (NULL);
    ray = safe_malloc(sizeof (t_ray), garbge);
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

t_tuple * ray_position(t_ray *ray, double t, t_list **garbge)
{
    t_tuple *pose;
    t_tuple *a_move;

    if (!ray || !ray->direction || !ray->origin)
        return (NULL);
    a_move = mul_tuple(ray->direction, t, garbge);
    pose = add_tuple(ray->origin, a_move, garbge);
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

t_sphere *create_sphere(t_list **garbge)
{
    t_sphere *sphere;
    double **arr;

    arr = create_arr(4, 4, garbge);
    arr[0][0] = 1;
    arr[1][1] = 1;
    arr[2][2] = 1;
    arr[3][3] = 1;
    sphere = safe_malloc(sizeof(t_sphere), garbge);
    sphere->center = create_point(0, 0, 0, garbge);
    sphere->transform = create_matrix(4, 4, (const double **)arr, garbge);
    sphere->material = create_material(garbge);
    sphere->r = 1;
    return (sphere);
}

t_intersect *create_intersect(t_list **garbge)
{
    t_intersect *intr;
    
    intr = safe_malloc(sizeof(t_intersect), garbge);
    intr->count = 0;
    intr->object = NULL;
    intr->t1 = -1;
    intr->t2 = -1;
    return (intr);
}

t_intersect *intersect(t_object *object, t_ray *ray, t_list **garbge)
{
    t_intersect *intr;        
    t_tuple *sphere_to_ray;
    t_ray *ray2;
    double a;
    double b;
    double c;
    double discriminant;
    
    if (!object || !object->shape || !ray)
        return (NULL);
    ray2 = transform(ray, matrix_inverse(object->shape->sphere->transform, garbge), garbge);
    intr = create_intersect(garbge);
    sphere_to_ray = sub_tuple(ray2->origin, object->shape->sphere->center, garbge);
    a = dot_tuple(ray2->direction, ray2->direction);
    b = 2 * dot_tuple(ray2->direction, sphere_to_ray);
    c = dot_tuple(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (intr);
    intr->object = object;
    intr->count = 2;
    intr->t1 = (-b - sqrt(discriminant)) / (2 * a);
    intr->t2 = (-b + sqrt(discriminant)) / (2 * a);
    return (intr);
}

void intersection(double t, t_object *object, e_type type, t_list **list, t_list **garbge)
{
    t_list *node;
    t_intersection *res;
    
    if (!object || !list || !object->shape)
        return ;
    
    res = safe_malloc(sizeof(t_intersection), garbge);
    res->t = t;
    res->object = safe_malloc(sizeof(t_object), garbge);
    res->object = object;
    res->object->type = type;
    node = ft_lstnew(res);
    add_to_garbge(garbge, node);
    ft_lstadd_back(list, node);
}
t_shape *create_shape(e_type type, t_list **garbge)
{
    t_shape *shape;

    shape = safe_malloc(sizeof(t_shape), garbge);
    if (type == SPHERE)
        shape->sphere = create_sphere(garbge);
    return (shape);
}

t_object *create_object(e_type type, t_list **garbge)
{
    t_object *object;
    
    object = NULL;
    object = safe_malloc(sizeof(t_object), garbge);
    object->shape = create_shape(type, garbge);
    object->material_seted = 0;
    return (object);
}

void free_object(t_object *object)
{
    if (!object)
        return ;
    if (!object->shape)
        return (free(object));
    if (object->type == SPHERE)
    {
        if (!object->shape->sphere)
            return (free(object->shape), free(object));
        if (object->material_seted == 1)
            free_material(object->shape->sphere->material);
        if (object->shape->sphere->center)
            free(object->shape->sphere->center);
        return (free(object->shape->sphere), free(object->shape), free(object));
    }
}

void print_intersections(t_list *list)
{
    int  i;

    i = 0;
    if (!list)
        return ;
    printf("list.size = %d\n",ft_lstsize(list));
    while (list)
    {
        printf("list[%d]->t = %f\n",i ,((t_intersection *)(list->content))->t);
        printf("list[%d]->object = %p\n",i ,((t_intersection *)(list->content))->object);
        list = list->next;
        i++;
    } 
}

void print_intersect(t_intersect *xs)
{
    if (!xs)
        return;
    printf("xs.count = %d\n",xs->count);
    printf("xs->object = %p\n",xs->object);
    printf("xs->t1 = %d\n",xs->t1);
    printf("xs->t2 = %d\n",xs->t2);
}

double hit(t_list *intr_list) // return a positive num if there is intersction accure , otherwise return negative number
{
    double res;
    double old;
    t_intersection *intr;
    

    res = -1;
    old = 0;
    while (intr_list)
    {
        intr = intr_list->content;
        old = intr->t;
        if ((old > 0 && old < res) || res < 0)
            res = old;
        intr_list = intr_list->next;
    }
    return (res);
}
double hit2(t_list *intr_list) // return a positive num if there is intersction accure , otherwise return negative number
{
    double res;
    double old;
    t_intersect *intr;
    

    res = -1;
    old = 0;
    while (intr_list)
    {
        intr = intr_list->content;
        if (intr->count != 0)
        {
            if (intr->t1 < intr->t2 && (intr->t1 > 0 && intr->t2 > 0))
                old = intr->t1;
            else if (intr->t1 > intr->t2 && (intr->t1 > 0 && intr->t2 > 0))
                old = intr->t2;
            if ((old > 0 && old < res) || res < 0)
                res = old;
        }
        intr_list = intr_list->next;
    }
    return (res);
}

t_ray *transform(t_ray *ray, t_matrix *matrix, t_list **garbge)
{
    t_ray *res;
    t_tuple *orgin;
    t_tuple *dir;

    if (!ray || !matrix)
        return (NULL);
    res = create_ray(orgin, dir, garbge);
    res->direction =  matrix_tuple_mul4x4(matrix, ray->direction, garbge);
    res->origin = matrix_tuple_mul4x4(matrix, ray->origin, garbge);
    return (res);
}

int  set_transform(t_object *object, t_matrix *matrix)
{
    if (!object || !object->shape || !matrix)
        return (-1);
    if (object->type == SPHERE)
        object->shape->sphere->transform = matrix;
    return (0);
}

t_tuple *normal_at(t_object *object, t_tuple *world_point, t_list **garbge)
{
    t_matrix *inverse;
    t_matrix *transpose;
    t_tuple *center;
    t_tuple *object_point;
    t_tuple *object_normal;
    t_tuple *world_normal;
    t_tuple *res;

    center = create_point(0, 0, 0, garbge);
    inverse = matrix_inverse(object->shape->sphere->transform, garbge);
    object_point = matrix_tuple_mul4x4(inverse, world_point, garbge);
    object_normal = sub_tuple(object_point, center, garbge);
    transpose = matrix_transpose4x4(inverse, garbge);
    world_normal = matrix_tuple_mul4x4(transpose, object_normal, garbge);
    world_normal->w = 0;
    res = norm_tuple(world_normal, garbge);
    return (res);
}

t_tuple *reflect(t_tuple *in, t_tuple *normal, t_list **garbge)
{
    t_tuple *mul;
    t_tuple *mul1;
    t_tuple *sub;

    mul = mul_tuple(normal, 2, garbge);
    mul1 = mul_tuple(mul, dot_tuple(in, normal), garbge);
    sub = sub_tuple(in, mul1, garbge);
    return (sub);
}

t_light *point_light(t_tuple *position, t_tuple *intensity, t_list **garbge)
{
    t_light *light;

    if (!position || !intensity)
        return (NULL);
    light = safe_malloc(sizeof(t_light), garbge);
    light->position = position;
    light->intensity = intensity;
    return (light);
}

t_material *create_material(t_list **garbge)
{
    t_material *mat;

    mat = safe_malloc(sizeof(t_material), garbge);
    mat->color = create_color(1, 1, 1, garbge);
    mat->ambient = 0.1;
    mat->diffuse = 0.9;
    mat->specular = 0.9;
    mat->shininess = 200.0;
    return (mat);
}

void free_material(t_material *m)
{
    if (!m)
        return ;
    if (!m->color)
        return (free(m));
    return (free(m->color), free(m));
}

int set_material(t_object *object, t_material *material)
{
    if (!object  || !object->shape || !material)
        return (-1);
    if (object->type == SPHERE)
    {
        object->shape->sphere->material = material;
        object->material_seted = 1;
    }
    return (0);
}

// TESTS
void draw_sphere(t_canvas *can, t_list **garbge)
{
    t_tuple *orgin;
    t_tuple *dir;
    t_ray *ray;
    t_tuple *color;
    t_object *object;
    t_intersect *xs;
    t_list *list;
    t_shearing *shr;

    double wall_z;
    double wall_size;
    double pixel_size;
    double half;
    shr = create_shearing(garbge);
    shr->xy = 1;

    if (!can || !can->mlx || !can->img || !can->img->img)
        return ;
    orgin = create_point(0, 0, -5, garbge);
    color = create_color(1, 0, 0, garbge);
    object = create_object(SPHERE, garbge);
    wall_z = 10;
    wall_size = 7;
    pixel_size = wall_size / can->height;
    half = wall_size / 2;

    object->shape->sphere->transform = matrix_multiply(shearing(shr, garbge), scaling(0.5, 1, 1, garbge), 4, garbge);
    int y;
    int x;
    y = -1;
    double world_x;
    double world_y;
    t_tuple *pose;
    int var;
    while (++y < can->height - 1)
    {
        world_y = half - pixel_size * y;
        x = -1;
        while (++x < can->height - 1)
        {
            world_x = -half + pixel_size * x;
            pose = create_point(world_x, world_y, wall_z, garbge);
            ray = create_ray(orgin, norm_tuple(sub_tuple(pose, orgin, garbge), garbge), garbge);
            xs = intersect(object, ray, garbge);
            list = ft_lstnew(xs);
            add_to_garbge(garbge, list);
            if (hit2(list) != -1)
                write_pixel(can, x, y, color);
        }
            var = (y * 100) / (can->height - 1);
            if (var)
            printf("[%d/100]\n",var);
    }
}
// MAIN -----------------------------------------------------------------------
    // t_canvas *can;
    // int canavas_pixel;
    // void *mlx;
    // void *win;
    // t_list **garbge;

    // mlx = mlx_init();
    // if (!mlx)
    //     return (-1);
    // canavas_pixel = 200;
    // win = mlx_new_window(mlx, canavas_pixel, canavas_pixel, "WIN");
    // if (!win)
    //     return (-1);
    // can = create_canvas(canavas_pixel, canavas_pixel, mlx);
    // draw_sphere(can, garbge);
    // mlx_put_image_to_window(mlx, win, can->img->img, 0, 0);
    // mlx_loop(mlx);

int main()
{
    t_object *object;
    t_material *m;
    t_list *garbge;
    t_list *tmp;

    garbge = NULL;
    object = create_object(SPHERE, &garbge);
    m = create_material(&garbge);
    m->ambient = 1;
    printf("%f\n",object->shape->sphere->material->ambient);
    set_material(object, m);
    printf("%f\n",object->shape->sphere->material->ambient);
    tmp = garbge;
    ft_lstclear(&garbge, free);
    
    t_canvas *can;
    int canavas_pixel;
    void *mlx;
    void *win;
    t_list *garbge;

    garbge = NULL;
    mlx = mlx_init();
    if (!mlx)
        return (-1);
    add_to_garbge(&garbge, mlx);
    canavas_pixel = 20;
    win = mlx_new_window(mlx, canavas_pixel, canavas_pixel, "WIN");
    if (!win)
        return (-1);
    add_to_garbge(&garbge, win);
    can = create_canvas(canavas_pixel, canavas_pixel, mlx, &garbge);
    printf("1\n");
    draw_sphere(can, &garbge);
    printf("2\n");
    mlx_put_image_to_window(mlx, win, can->img->img, 0, 0);
    printf("3\n");
    printf("DONE\n");
    mlx_loop(mlx);
    ft_lstclear(&garbge, free);
}