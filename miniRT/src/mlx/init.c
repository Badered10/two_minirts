#include "../../includes/main.h"

void    **mlx()
{
    static void *mlx = NULL;

    return (&mlx);
}

void   **mlx_win()
{
    static void *win = NULL;

    return (&win);
}

t_data  *data()
{
    static t_data  data;

    return (&data);
}

void    flush()
{
    mlx_put_image_to_window(*mlx(), *mlx_win(), data()->img, 0, 0);
}
