#ifndef MAIN_H
#define MAIN_H

# include "../mlx_mac/mlx.h"
# include "../libft/libft.h"
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

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# ifdef WIN_WIDTH
#  undef WIN_WIDTH
# endif

# ifdef WIN_HEIGHT
#  undef WIN_HEIGHT
# endif

# ifdef __APPLE__
#  define WIN_WIDTH 1280
#  define WIN_HEIGHT 720
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 720
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 480
# endif

# define WIN_TITLE "MiniRT"

// map:
scene_t *scene();

// writers
void    insert_light(light_t *light);
void    insert_ambient_light(ambient_light_t *a_light);
void    insert_cylinder(cylinder_t *cylinder);
void    insert_plane(plane_t *plane);
void    insert_sphere(sphere_t *sphere);

void    print_scene_data();
void    read_map_data(char *filename);

// mlx:
void    **mlx();
void    **mlx_win();
t_data  *data();
void	put_pixel(int x, int y, int color);
void    flush();
void    events();

bool    is_in_fov(space_point_t *center);
void    render();

#endif