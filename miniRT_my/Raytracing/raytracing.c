#include "../parse/minirt.h"

#define DEF 0x0303fc
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define WIDTH 800
#define HEIGHT 800

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


int	key_hook(int keycode, t_rt *rt)
{
    (void)rt;
	printf("%d \n", keycode);
    if (keycode == 119)
    {
        ;
    }
    else if (keycode == 115)
    {
        ;
    }
    else if (keycode == 100)
    {
        ;
    }
    else if (keycode == 97)
    {
        ;
    }
    else if (keycode == 53)
    {
        exit (0);
    }
	return (0);
}

int main()
{
    t_rt rt;
    
    rt.mini.mlx = mlx_init();
    if (!rt.mini.mlx) {
        perror("mlx_init failed");
        return (1);
    }

    rt.mini.window = mlx_new_window(rt.mini.mlx, WIDTH, HEIGHT, "My window");
    if (!rt.mini.window) 
    {
        perror("mlx_new_window failed");
        return (1);
    }

    rt.mini.img.img = mlx_new_image(rt.mini.mlx, WIDTH, HEIGHT);
    if (!rt.mini.img.img)
    {
        perror("mlx_new image failed");
        return (1);
    }

    rt.mini.img.addr = mlx_get_data_addr(rt.mini.img.img, &rt.mini.img.bits_per_pixel, &rt.mini.img.line_length, &rt.mini.img.endian);
    if (!rt.mini.img.addr)
    {
        perror("mlx_get_address failed");
        return (1);
    }
    mlx_put_image_to_window(rt.mini.mlx, rt.mini.window, rt.mini.img.img, 0, 0);
    mlx_key_hook(rt.mini.window, &key_hook, &rt);
    mlx_loop(rt.mini.mlx);
}