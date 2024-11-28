#include "main.h"

void insert_light(light_t *light)
{
    light_t *light_node;

    light_node = scene()->light_list;

    if (!light_node)
    {
        scene()->light_list = light;
        return ;
    }

    while (light_node->next)
        light_node = light_node->next;

    light_node->next = light;
}

void insert_ambient_light(ambient_light_t *a_light)
{
    ambient_light_t *a_light_node;

    a_light_node = scene()->ambient_light_list;

    if (!a_light_node)
    {
        scene()->ambient_light_list = a_light;
        return ;
    }

    while (a_light_node->next)
        a_light_node = a_light_node->next;

    a_light_node->next = a_light;
}

void insert_cylinder(cylinder_t *cylinder)
{
    cylinder_t *cylinder_node;

    cylinder_node = scene()->cylinder_list;

    if (!cylinder_node)
    {
        scene()->cylinder_list = cylinder;
        return ;
    }

    while (cylinder_node->next)
        cylinder_node = cylinder_node->next;

    cylinder_node->next = cylinder;
}

void insert_plane(plane_t *plane)
{
    plane_t *plane_node;

    plane_node = scene()->plane_list;

    if (!plane_node)
    {
        scene()->plane_list = plane;
        return ;
    }

    while (plane_node->next)
        plane_node = plane_node->next;

    plane_node->next = plane;
}

void insert_sphere(sphere_t *sphere)
{
    sphere_t *sphere_node;

    sphere_node = scene()->sphere_list;

    if (!sphere_node)
    {
        scene()->sphere_list = sphere;
        return ;
    }

    while (sphere_node->next)
        sphere_node = sphere_node->next;

    sphere_node->next = sphere;
}
