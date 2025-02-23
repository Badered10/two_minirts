#ifndef TOOLS_H
#define TOOLS_H

# include "libs.h"
# include "/home/baouragh/Desktop/two_minirts/miniRT_my/libft/libft.h"


typedef enum s_type
{
    SPHERE,
    PLANE,
    CYLINDER
} e_type;


// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_list;

// t_list				*ft_lstnew(void *content);
// void				ft_lstadd_front(t_list **lst, t_list *new_list);
// int					ft_lstsize(t_list *lst);
// t_list				*ft_lstlast(t_list *lst);
// void				ft_lstadd_back(t_list **lst, t_list *new_list);
// void				ft_lstdelone(t_list *lst, void (*del)(void *));
// void				ft_lstclear(t_list **lst, void (*del)(void *));
// void				ft_lstiter(t_list *lst, void (*f)(void *));
// t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
// 						void (*del)(void *));




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
    void *mlx;
    t_img *img;
} t_canvas;

typedef struct s_tuple
{
    double     x;
    double     y;
    double     z;
    double     w;
}   t_tuple;
typedef struct s_matrix
{
    int size;
    double **data;
} t_matrix;

typedef struct s_material
{
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    t_tuple *color;
} t_material;


// typedef struct flat_point_s
// {
//     double     x;
//     double     y;
// }   flat_point_t;


// typedef struct color_s
// {
//     unsigned short  r;
//     unsigned short  g;
//     unsigned short  b;
// }   color_t;

typedef struct s_ambient
{
    double   lighting_ratio;
    t_tuple  *color;
    // struct s_ambient *next;
}   t_ambient;

typedef struct s_camera
{
    t_tuple   *pos;
    t_tuple   *direction;
    double field_of_view;
    double hsize;
    double vsize;
    double half_width;
    double half_height;
    double pixel_size;
    t_matrix *transform;
}   t_camera;

typedef struct s_light
{
    double           brightness; //t_tuple *intensity TO DO // NOT MINE
    t_tuple         *position;
    t_tuple         *color;
    t_tuple         *intensity;
    // struct s_light  *next;
}   t_light;

typedef struct s_sphere
{
    t_tuple      *pos;
    double       diameter; // r / 2
    // t_tuple      *color;
    // struct s_sphere *next;
}   t_sphere;

typedef struct s_plane
{
    t_tuple   *pos; // center
    t_tuple   *normal; // [-1, 1] [-1, 1] [-1, 1]
    // t_tuple   *color;
    // struct s_plane  *next;
}   t_plane;

typedef struct t_cylinder
{
    t_tuple       *center;
    t_tuple       *normal; // [-1, 1] [-1, 1] [-1, 1]
    double         diameter;
    double         height;
    // t_tuple        *color;
    // struct s_cylinder   *next;
}   t_cylinder;

typedef union s_shape
{
    t_sphere *sphere;
    t_plane *plane;
    t_cylinder *cylinder;
} t_shape;

typedef struct s_object
{
    e_type type;
    t_shape *shape;
    t_matrix *transform;
    t_material *material;
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

typedef struct s_shearing
{
    double xy;
    double xz;
    double yx;
    double yz;
    double zx;
    double zy;
} t_shearing;

typedef struct s_world
{
    t_camera                *camera;
    t_list                  *lights_list;
    t_list                  *objects_list;
    t_list                  *ambient_list;
    int                     ambient_count;
    int                     light_count;
}   t_world;


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

typedef struct s_ray
{
    t_tuple *origin;
    t_tuple *direction;
} t_ray;

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
t_light *point_light(double brightness, t_tuple *position, t_tuple *color);
t_matrix *view_transform(t_tuple *from, t_tuple *to, t_tuple *up);
t_object *create_object(e_type type);
t_sphere *create_sphere(void);
t_tuple *create_color(double x, double y, double z);
bool is_shadowed(t_world *world, t_tuple *point);
t_xs *intersect(t_object *object, t_ray *ray);
t_matrix *identity_matrix(void);
t_tuple *cross_tuple(t_tuple *a, t_tuple *b);

#endif