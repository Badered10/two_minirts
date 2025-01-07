#include "geo.h"

// DEBUG FUNCTION-------------------------------------------------------------------------------
void print_type(t_tuple *tuple)
{
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
t_tuple *creat_tuple(double x, double y, double z, double w)
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

t_tuple *creat_point(double x, double y, double z)
{
    return (creat_tuple(x, y, z, 1));
}

t_tuple *creat_vector(double x, double y, double z)
{
    return (creat_tuple(x, y, z, 0));
}

t_tuple *creat_color(double x, double y, double z)
{
    return (creat_tuple(x, y, z, 20));
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
    return (creat_tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w));
}

t_tuple *sub_tuple(t_tuple *a, t_tuple *b)
{
    return (creat_tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w));
}

t_tuple *negate_tuple(t_tuple *a)
{
    return (creat_tuple(-a->x, -a->y, -a->z, -a->w));
}

t_tuple *mul_tuple(t_tuple *a, double b)
{
    return (creat_tuple(a->x * b, a->y * b, a->z * b, a->w * b));
}

t_tuple *div_tuple(t_tuple *a, double b)
{
    return (creat_tuple(a->x / b, a->y / b, a->z / b, a->w / b));
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
    return (creat_vector(a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x));
}

t_tuple *hadamard_product(t_tuple *a, t_tuple *b)
{
    return (creat_color(a->x * b->x, a->y * b->y, a->z * b->z));
}

// PROJECTILE FUNCS--------------------------------------------------------------------------

t_projectile *creat_projectile(t_tuple *position, t_tuple *speed)
{
    t_projectile *projectile = malloc(sizeof(t_projectile));
    if (projectile == NULL)
        return (NULL);

    projectile->position = position;
    projectile->speed = speed;

    return (projectile);
}

t_environment *creat_environment(t_tuple *gravity, t_tuple *wind)
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

    return (creat_projectile(position, speed));
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

t_canvas * creat_canvas(int width , int height, void *mlx_ptr)
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

    return (creat_color(r, g, b));
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

typedef struct s_matrix
{
    int rows_num;
    int colums_num;
    double **data;
} t_matrix;

void free_matrix(t_matrix *matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return;
    while (i < matrix->rows_num)
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

    if (rows <= 0 || colums <= 0)
        return (NULL);
    matrix = malloc(sizeof(t_matrix));
    if (!matrix)
        return (NULL);
    matrix->rows_num = rows;
    matrix->colums_num = colums;
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
    if (i > m->rows_num || i < 0 || j > m->colums_num || j < 0)
        return (printf("ERROR : MATRIX OUT OF RANGE\n"), -1);

    return (m->data[i][j]);    
}

void print_matrix(t_matrix *m)
{
    int i;
    int j;

    i = 0;
    while (i < m->rows_num)
    {
        j = 0;
        while (j < m->colums_num)
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
         m1->colums_num != m2->colums_num || m1->rows_num != m2->rows_num)
        return (0);
    i = 0;
    while (i < m1->rows_num)
    {
        j = 0;
        while (j < m1->colums_num)
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

    if (!a || !b || !a->data || !b->data 
        || a->colums_num != size || a->rows_num != size
        || b->colums_num != size || b->rows_num != size)
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

    if (!a || !t || !a->data || a->colums_num != 4 || a->rows_num != 4)
        return (0);
    tuple = creat_tuple(0, 0, 0, 0);
    i = 0;
    while (i < 4)
    {
        res =   a->data[i][0] * t->x 
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

double matrix_determinant2x2(t_matrix *matrix)
{
    if (!matrix || !matrix->data)
        return (0);
    return ((matrix->data[0][0] * matrix->data[1][1]) - (matrix->data[0][1] * matrix->data[1][0]));
}

void remove_row_cols(t_matrix *matrix, t_matrix *submatrix, int row, int column)
{
    int i;
    int j;
    int new_row;
    int new_col;

    i = -1;
    new_row = 0;
    while (++i < matrix->rows_num)
    {
        j = -1;
        new_col = 0;
        if (i != row)
        {
            while (++j < matrix->colums_num)
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

    if (!matrix || !matrix->data || matrix->colums_num <= column || matrix->rows_num <= row)
        return (NULL);
    submatrix = create_matrix(matrix->rows_num - 1, matrix->colums_num - 1, NULL);
    if (!submatrix)
        return (NULL);
    remove_row_cols(matrix ,submatrix, row, column);
    return (submatrix);
}

double matrix_minor3x3(t_matrix *matrix, int row, int column)
{
    t_matrix *sub;
    double  res;

    sub = sub_matrix(matrix, row, column);
    if (!sub)
        return (0);
    res = matrix_determinant2x2(sub);
    free_matrix(sub);
    return (res);
}

// MAIN -----------------------------------------------------------------------

int main()
{
    // t_projectile *projectile;
    // t_environment *env;
    // t_tuple *pose;
    // t_tuple *speed;
    // t_tuple *gravity;
    // t_tuple *wind;
    // void *mlx;
    // void *win;
    // void *img;
    // t_canvas *canvas;
    // t_tuple  *red;

    // pose = creat_point(0, 1, 0);
    // speed = creat_vector(1, 1.8, 0);
    // gravity = creat_vector(0, -0.1, 0);
    // wind = creat_vector(-0.01, 0, 0);
    // env = creat_environment(gravity, wind);
    // projectile = creat_projectile(pose, mul_tuple(norm_tuple(speed), 11.25));
    // mlx = mlx_init();
    // if (!mlx)
    //     return(-1);
    // win = mlx_new_window(mlx, 900, 550, "test");
    // if (!win)
    //     return (-2);
    // canvas = creat_canvas(900, 550, mlx);
    // if (!canvas)
    //     return (-3);
    
    // red = creat_color(1, 0, 0);

    // while (projectile->position->y > 0)
    // {
    //     projectile = tick(env, projectile);
    //     print_type(projectile->position);
    //     if (projectile->position->y < 0 || projectile->position->x < 0)
    //         break;
    //     if (900 - projectile->position->x >= 0 && 550 - projectile->position->y >= 0)
    //     {
    //         write_pixel(canvas, 900 - projectile->position->x, 550 - projectile->position->y, red);
    //         printf("%f, %f \n", 900 - projectile->position->x, 550 - projectile->position->y);
    //     }
    // }

    // print_type(pixel_at(canvas, 0, 0));
    // print_type(pixel_at(canvas, 1, 1));
    // mlx_put_image_to_window(mlx, win, canvas->img->img, 0, 0);
    // mlx_loop(mlx);
    t_matrix *matrix;
    t_matrix *matrix1;
    t_matrix *matrix2;
    t_matrix *identity_matrix;
    t_matrix *res;
    t_tuple *tuple;

    double arr[4][4] = {{-6,1,1,6}, {-8,5,8,6}, {-1,0,8,2}, {-7,1,-1,1}};
    double arr1[3][3] = {{3,5,0}, {2,-1,7}, {6,-1,5}};
    double arr2[4][4] = {{0,9,3,0}, {9,8,0,8}, {1,8,5,3}, {0,0,5,8}};
    double arr3[4][4] = {{1,2,3,4}, {2,4,4,2}, {8,6,4,1}, {0,0,0,1}};
    double arr4[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};

    double arr5[2][2] = {{1,5}, {-3,2}};

    const double *input0[3] = {arr1[0], arr1[1], arr1[2]};
    const double *input1[4] = {arr[0], arr[1], arr[2], arr[3]};
    const double *input2[4] = {arr2[0], arr2[1], arr2[2], arr2[3]};
    const double *input3[4] = {arr3[0], arr3[1], arr3[2], arr3[3]};
    const double *input4[4] = {arr4[0], arr4[1], arr4[2], arr4[3]};
    const double *input5[2] = {arr5[0], arr5[1]};

    matrix = create_matrix(2, 2, input5);
    matrix1 = create_matrix(3, 3, input0);
    matrix2 = create_matrix(4, 4, input1);
    res = create_matrix(4, 4, input3);
    identity_matrix = create_matrix(4, 4, input4);

    tuple = creat_tuple(1, 2, 3, 1);
    // res = sub_matrix(matrix2, 2, 1);
    // print_matrix(res);
    printf("%f\n",matrix_minor3x3(matrix1, 1, 0));
    free_matrix(res);
    free_matrix(matrix);
    free(tuple);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(identity_matrix);
    return 0;

}