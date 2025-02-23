#ifndef MAIN_H
#define MAIN_H

# include "../mlx_mac/mlx.h"
// # include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "libs.h"
# include "tools.h"
# include "gc.h"
# include "error.h"
# include "guards.h"

# define MAX_SCENE_ITEMS 100

# define DOUBLE_MAX 1000000
# define DOUBLE_MIN -1000000

# ifndef DEBUG
#  define DEBUG 0
# endif

// #ifndef M_PI
// # define M_PI 3.14159265358979323846
// #endif

// # ifdef WIDTH
// #  undef WIDTH
// # endif

// # ifdef HEIGHT
// #  undef HEIGHT
// # endif

// # ifdef __APPLE__
// #  define WIDTH 1280
// #  define HEIGHT 720
// # endif

// # ifndef WIDTH
// #  define WIDTH 720
// # endif

// # ifndef HEIGHT
// #  define HEIGHT 480
// # endif

#define WIDTH 200
#define HEIGHT 100

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

#define EPSILON 1e-5
#define PI      3.14159265358979323846

# define WIN_TITLE "MiniRT"

// map:
t_world *scene();

// writers
// void    insert_light(t_light *light);
// void    insert_ambient_light(t_ambient *a_light);
// void    insert_cylinder(t_cylinder *cylinder);
// void    insert_plane(t_plane *plane);
// void    insert_sphere(t_sphere *sphere);

void    print_scene_data();
void    read_map_data(char *filename);

// mlx:
void    **mlx();
void    **mlx_win();
t_img   *data();
void	put_pixel(int x, int y, int color);
void    flush();
void    events();

bool    is_in_fov(t_tuple *center);
char	**ft_c_split(char const *s, char *separators);
void    to_render();

#endif