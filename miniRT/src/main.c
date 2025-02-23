#include "../includes/main.h"

void    ac_guard(int ac)
{
    if (ac < 2)
    {
        ft_putstr_fd("Missing arguments\n", 2);
        exit(1);
    }
}

void    init()
{
    *mlx() = mlx_init();
    *mlx_win() = mlx_new_window(*mlx(), WIDTH, HEIGHT, WIN_TITLE);
    data()->img = mlx_new_image(*mlx(), WIDTH, HEIGHT);
    data()->addr = mlx_get_data_addr(data()->img, &data()->bits_per_pixel, &data()->line_length, &data()->endian);
}

int main(int ac, char **av)
{
    if (DEBUG)
        printf("Debug mode\n");

    ft_bzero(scene(), sizeof(t_world *));
    ac_guard(ac);
    
    read_map_data(av[1]);

    print_scene_data();

    init();

    // render();

    flush();
    events();
    mlx_loop((*mlx()));

    return 0;
}
