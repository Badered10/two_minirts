#include "../parse/minirt.h"
#include "../ray/ray.h"
#include "../vec3/vec3.h"
#include "../color/color.h"
#include <stdio.h>
#include <stdlib.h>


#define DEF 0x0303fc
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define WIDTH 1200
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
    return ;
    
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

void insert_scene(t_rt *rt)
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

void insert_cercle(t_rt *rt, int a, int b, int r, int color)
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

// void insert_sphere(t_rt *rt, int x, int y, int color)
// {
//     t_vec3 ray_origin;
//     t_vec3 ray_direction;
//     double r = 0.5; // radius of the sphere
//     // int dist; // distance between center of circle and point

//     // cercle equation : (X)² + (Y)² - r² = 0 , while  center coords is (0, 0)
//     // vector equation is : a + tb .

//     // ax + bxt = X
//     // ay + bxt = Y

//     // (ax + bxt)² + (ay + byt)² - r² = 0
//     // ax² + 2axbxt + bx²t² + ay² + 2aybyt + by²t² - r² = 0
//     // (bx² + by²)t² + (2(axbx + ayby))t + (ax² + ay² - r²) = 0
    
//     // let's solve for t: 
//     // t = (-b ± √(b² - 4ac)) / 2a

//     // a is ray origin
//     // b is ray direction
//     // r is the radius of the sphere
//     // t is hit distance

//     double a = vec3_dot(ray_direction , ray_direction);
//     double b = 2 * vec3_dot(ray_direction, ray_origin);
//     double c = vec3_dot(ray_origin, ray_origin) - r * r;


//     // x = 0;
//     // while (x < WIDTH)
//     // {
//     //     y = 0;
//     //     while (y < HEIGHT)
//     //     {
//     //         dist = (x - a) * (x - a) + (y - b) * (y - b);
//     //         if (dist <= r * r)
//     //             my_mlx_pixel_put(&rt->mini.img, x, y, color);
//     //         y++;
//     //     }
//     //     x++;
//     // }


// }


int main()
{
    t_rt rt;

    float aspect_ratio;
    int image_width;
    int image_height;
    float focal_length;
    float viewport_height;
    float viewport_width;
    t_vec3 viewport_u;
    t_vec3 viewport_v;
    t_vec3 pixel_delta_u;
    t_vec3 pixel_delta_v;
    t_vec3 viewport_upper_left;
    t_vec3 pixel00_loc;
    t_point3 camera_center;

    // image 
    image_width = WIDTH;
    aspect_ratio = 16.0 / 9.0;

    // Calculate the image height, and ensure that it's at least 1.
    image_height = (int)(image_width / aspect_ratio);
    if (image_height < 1)
        image_height = 1;

    // camera
    focal_length = 1.0;
    viewport_height = 2.0;
    viewport_width = viewport_height * ((double)(image_width) / image_height);
    camera_center = create_point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // pixel_delta_u = viewport_u / image_width;
    // pixel_delta_v = viewport_v / image_height;
    pixel_delta_u = vec3_scale(viewport_u, 1.0 / image_width);
    pixel_delta_v = vec3_scale(viewport_v, 1.0 / image_height);

    // Calculate the location of the upper left pixel.
    // viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    // pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    viewport_upper_left = vec3_sub(camera_center, vec3_add(vec3_scale(vec3(0, 0, focal_length), 1), vec3_scale(viewport_u, 0.5)));
    pixel00_loc = vec3_add(viewport_upper_left, vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    // Render

    printf("P3\n%d %d\n255\n", image_width, image_height);
    rt.mini.mlx = mlx_init();
    if (!rt.mini.mlx) {
        perror("mlx_init failed");
        return (1);
    }

    rt.mini.window = mlx_new_window(rt.mini.mlx, image_width, image_height, "My window");
    if (!rt.mini.window) 
    {
        perror("mlx_new_window failed");
        return (1);
    }

    rt.mini.img.img = mlx_new_image(rt.mini.mlx, image_width, image_height);
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

    for (int j = 0; j < image_height; j++) 
    {
        fprintf(stderr, "\rScanlines remaining: %d ", (image_height - j));
        fflush(stderr);
        for (int i = 0; i < image_width; i++) 
        {
            t_vec3 pixel_center = vec3_add(pixel00_loc, vec3_add(vec3_scale(pixel_delta_u, i), vec3_scale(pixel_delta_v, j)));
            t_vec3 ray_direction = vec3_sub(pixel_center, camera_center);
            t_ray r = create_ray(camera_center, ray_direction);
            t_color pixel_color;
            pixel_color = ray_color(r);
            int color = ((int)(255.999 * pixel_color.x) << 16) | ((int)(255.999 * pixel_color.y) << 8) | (int)(255.999 * pixel_color.z);
            my_mlx_pixel_put(&rt.mini.img, i, image_height - j - 1, color);
            // write_color(pixel_color);
        }
    }

    // insert_scene(&rt);
    // insert_cercle(&rt, 400, 400, 100, 0x00ff00);
    mlx_put_image_to_window(rt.mini.mlx, rt.mini.window, rt.mini.img.img, 0, 0);
    mlx_key_hook(rt.mini.window, &key_hook, &rt);
    mlx_hook(rt.mini.window, 17, 0, &close_win, &rt);
    mlx_loop(rt.mini.mlx);
}