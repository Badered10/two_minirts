#include "h.h"
#include <fcntl.h>
#include <unistd.h>

void set_ambient_light(t_world *world, double ratio, t_tuple *color)
{
    world->ambient_light = ratio;
    world->ambient_color = color;
}

void parse_ambient(char **tokens, t_world *world)
{
    double ratio = atof(tokens[1]);
    int r, g, b;
    sscanf(tokens[2], "%d,%d,%d", &r, &g, &b);
    t_tuple *color = create_color(r / 255.0, g / 255.0, b / 255.0);
    // Assuming you have a function to set ambient light in the world
    set_ambient_light(world, ratio, color);
}



void parse_camera(char **tokens, t_camera **cam)
{
    double x, y, z, vx, vy, vz, fov;
    sscanf(tokens[1], "%lf,%lf,%lf", &x, &y, &z);
    sscanf(tokens[2], "%lf,%lf,%lf", &vx, &vy, &vz);
    fov = atof(tokens[3]);

    *cam = create_camera(800, 600, fov * (PI / 180));
    (*cam)->transform = view_transform(create_point(x, y, z), create_point(vx, vy, vz), create_vector(0, 1, 0));
}

void parse_light(char **tokens, t_world *world)
{
    double x, y, z, brightness;
    int r, g, b;
    sscanf(tokens[1], "%lf,%lf,%lf", &x, &y, &z);
    brightness = atof(tokens[2]);
    sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);
    t_tuple *color = create_color(r / 255.0, g / 255.0, b / 255.0);

    t_light *light = point_light(create_point(x, y, z), color);
    ft_lstadd_front(&world->lights_list, ft_lstnew(light));
}

void parse_sphere(char **tokens, t_world *world)
{
    double x, y, z, diameter;
    int r, g, b;
    sscanf(tokens[1], "%lf,%lf,%lf", &x, &y, &z);
    diameter = atof(tokens[2]);
    sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);

    t_object *sphere = create_object(SPHERE);
    sphere->shape->sphere->transform = matrix_multiply(translation(x, y, z), scaling(diameter / 2, diameter / 2, diameter / 2), 4);
    sphere->shape->sphere->material = create_material();
    sphere->shape->sphere->material->color = create_color(r / 255.0, g / 255.0, b / 255.0);

    ft_lstadd_front(&world->objects_list, ft_lstnew(sphere));
}

void parse_plane(char **tokens, t_world *world)
{
    double x, y, z, nx, ny, nz;
    int r, g, b;
    sscanf(tokens[1], "%lf,%lf,%lf", &x, &y, &z);
    sscanf(tokens[2], "%lf,%lf,%lf", &nx, &ny, &nz);
    sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);

    t_object *plane = create_object(PLANE);
    plane->shape->plane->transform = translation(x, y, z); // Assuming you have a plane object
    plane->shape->plane->material = create_material();
    plane->shape->plane->material->color = create_color(r / 255.0, g / 255.0, b / 255.0);

    ft_lstadd_front(&world->objects_list, ft_lstnew(plane));
}

// void parse_cylinder(char **tokens, t_world *world)
// {
//     double x, y, z, vx, vy, vz, diameter, height;
//     int r, g, b;
//     sscanf(tokens[1], "%lf,%lf,%lf", &x, &y, &z);
//     sscanf(tokens[2], "%lf,%lf,%lf", &vx, &vy, &vz);
//     diameter = atof(tokens[3]);
//     height = atof(tokens[4]);
//     sscanf(tokens[5], "%d,%d,%d", &r, &g, &b);

//     t_object *cylinder = create_object(CYLINDER);
//     cylinder->shape->cylinder->transform = matrix_multiply(translation(x, y, z), scaling(diameter / 2, height, diameter / 2), 4);
//     cylinder->shape->cylinder->material = create_material();
//     cylinder->shape->cylinder->material->color = create_color(r / 255.0, g / 255.0, b / 255.0);

//     ft_lstadd_front(&world->objects_list, ft_lstnew(cylinder));
// }

void parse_file(const char *filename, t_world *world, t_camera **cam)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *line;
    while ((line = get_next_line(fd)))
    {
        char **tokens = ft_split(line, ' ');
        if (tokens[0][0] == 'A')
        {
            parse_ambient(tokens, world);
            printf("Parsed ambient light\n");
        }
        else if (tokens[0][0] == 'C')
        {
            parse_camera(tokens, cam);
            printf("Parsed camera\n");
        }
        else if (tokens[0][0] == 'L')
        {
            parse_light(tokens, world);
            printf("Parsed light\n");
        }
        else if (tokens[0][0] == 's' && tokens[0][1] == 'p')
        {
            parse_sphere(tokens, world);
            printf("Parsed sphere\n");
        }
        else if (tokens[0][0] == 'p' && tokens[0][1] == 'l')
        {
            parse_plane(tokens, world);
            printf("Parsed plane\n");
        }
        // else if (tokens[0][0] == 'c' && tokens[0][1] == 'y')
        // {
        //     parse_cylinder(tokens, world);
        //     printf("Parsed cylinder\n");
        // }
        free(line);
        free(tokens);
    }
    close(fd);
}