/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:17:09 by baouragh          #+#    #+#             */
/*   Updated: 2025/01/17 15:47:47 by baouragh         ###   ########.fr       */
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
    return (create_tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w));
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

    canvas = malloc(sizeof(t_canvas));
    if (!canvas)
        return (NULL);
    canvas->width = width;
    canvas->height = height;
    canvas->img = new_img(width, height, mlx_ptr);
    if (!canvas->img)
        return (NULL);
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

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *red)
{
    my_mlx_pixel_put(canvas->img, x, y, color_to_int(red));
}

t_tuple *pixel_at(t_canvas *canvas, int x, int y)
{ 
    int color;

    color = color_at(canvas->img, x, y);
    return (int_to_color(color));
}

// MATRIXS INTO THE SCENE------------------------------------------------------------
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

double **duplicate_array(int rows, int colums, const double *arr[])
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

t_matrix *create_matrix(int rows, int colums, const double *arr[])
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
        return (0);
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

    if (!matrix || !matrix->data || !matrix_invertiblity(matrix))
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
    matrix->data[2][1] = 1;
    
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
    memset(shearing, 0, sizeof(t_shearing));
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

t_sphere *create_sphere(void)
{
    t_sphere *sphere;
    
    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);
    sphere->center = create_point(0, 0, 0);
    if (!sphere->center)
        return (free(sphere), NULL);
    sphere->r = 1;
    return (sphere);
}

t_intersect *create_intersect(double i1, double i2, bool init)
{
    t_intersect *intr;
    
    intr = malloc (sizeof(t_intersect));
    if (!intr)
        return (NULL);
    intr->value = malloc(sizeof(double) * 2);
    if (!intr->value)
        return(free(intr), NULL);
    if (init)
    {
        intr->count = 2;
        intr->value[0] = i1;
        intr->value[1] = i2;
    }
    else
    {
        intr->count = 0;
        intr->value[0] = 0;
        intr->value[1] = 0;
    }
    return (intr);
}

t_intersect *intersect(t_object *object, t_ray *ray)
{
    t_intersect *intr;
    t_tuple *sphere_to_ray;
    double a;
    double b;
    double c;
    double discriminant;
    
    if (!object || !ray)
        return (NULL);
    intr = create_intersect(0, 0, 0);
    if (!intr)
        return (NULL);
    
    sphere_to_ray = sub_tuple(ray->origin, object->sphere->center);
    a = dot_tuple(ray->direction, ray->direction);
    b = 2 * dot_tuple(ray->direction, sphere_to_ray);
    c = dot_tuple(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = b * b - 4 * a * c;
    free(sphere_to_ray);
    if (discriminant < 0)
        return (intr);
    intr->count = 2;
    intr->value[0] = (-b - sqrt(discriminant)) / (2 * a);
    intr->value[1] = (-b + sqrt(discriminant)) / (2 * a);
    return (intr);
}

void intersection(double t, t_object *object, e_type type, t_list **list)
{
    t_list *node;
    t_intersection *res;
    
    if (!object || !list)
        return ;
    
    res = malloc(sizeof(t_intersection));
    if (!res)
        return ;
    res->t = t;
    res->object = malloc(sizeof(t_data));
    if (!res->object)
        return (free(res),(void)0);
    res->object->data = object;
    res->object->type = type;
    node = ft_lstnew(res);
    if (!node)
        return(free(res->object), free(res), (void)0);
    ft_lstadd_back(list, node);
}

t_object *create_object(void *data, e_type type)
{
    t_object *object;
    
    object = NULL;
    if (!data)
        return (NULL);
    object = malloc(sizeof(t_object));
    if (!object)
        return (NULL);
    if (type == SPHERE)
        object->sphere = data;
    return (object);
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
        printf("list[%d].t = %f\n",i ,((t_intersection *)(list->content))->t);
        list = list->next;
        i++;
    } 
}

void print_intersect(t_intersect *xs)
{
    if (!xs)
        return;
    printf("xs.count = %d\n",xs->count);
    printf("xs[0].object = %d\n",xs->value[0]);
    printf("xs[1].object = %d\n",xs->value[1]);
}

// MAIN -----------------------------------------------------------------------

int main()
{
    t_object *object;
    t_sphere *s;
    t_list *list;
    t_intersect *xs;
    t_ray *ray;
    t_tuple *origin;
    t_tuple *dir;
    
    object = NULL;
    list = NULL;
    
    origin = create_point(0, 0 , -5);
    dir = create_vector(0, 0 , 1);
    ray = create_ray(origin, dir);
    s = create_sphere();
    object = create_object(s, SPHERE);
    intersection(1, object, SPHERE, &list);
    intersection(2, object, SPHERE, &list);

    xs = intersect(s, ray);

    print_intersections(list);
    
    return (0);
}