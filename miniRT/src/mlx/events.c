#include "../../includes/main.h"

#ifdef __linux__
    enum e_keys
    {
        ESC = 65307,
    };
#endif

#ifdef __APPLE__
    enum e_keys
    {
        ESC = 53,
    };
#endif

int	event_mapper(int keycode)
{

    if (keycode == ESC)
    {
        mlx_destroy_window(*mlx(), *mlx_win());
        clean_();
        exit(0);
    }

	printf("Keycode: %d\n", keycode);
	return (0);
}

void    events()
{
    mlx_key_hook(*mlx_win(), event_mapper, NULL);
}
