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

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int close_win(t_rt *rt)
{
    (void)rt;
    exit(1);
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
    else if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(rt->mini.mlx, rt->mini.window);
        exit (0);
    }
	return (0);
}

int add_gradient(int x , int y)
{
    int scaled_y;
    int scaled_x;

    scaled_x = x * 255 / WIDTH;
    scaled_y = y * 255 / HEIGHT;

    return ((scaled_y << 16) | (scaled_x << 8));
}

void draw_scene(t_rt *rt)
{
    int x;
    int y;

    y = 0;
    while (y < WIDTH)
    {
        x = 0;
        while (x < HEIGHT)
        {
            my_mlx_pixel_put(&rt->mini.img, x , y, add_gradient(x, y));
            x++;
        }
        y++;
    }
}

void draw_cercle(t_rt *rt, int a, int b, int r, int color)
{
    int x; // x coord of circle
    int y; // y coord of circle
    int dist; // distance between center of circle and point

    // (x - a)² + (y - b)² = r²

    // a is the x coord of the center of the circle
    // b is the y coord of the center of the circle
    // r is the radius of the circle

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            dist = (x - a) * (x - a) + (y - b) * (y - b);
            if (dist <= r * r)
                my_mlx_pixel_put(&rt->mini.img, x, y, color);
            y++;
        }
        x++;
    }
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

    draw_scene(&rt);
    draw_cercle(&rt, 400, 400, 100, 0x00ff00);
    mlx_put_image_to_window(rt.mini.mlx, rt.mini.window, rt.mini.img.img, 0, 0);
    mlx_key_hook(rt.mini.window, &key_hook, &rt);
    mlx_hook(rt.mini.window, 17, 0, &close_win, &rt);
    mlx_loop(rt.mini.mlx);
}