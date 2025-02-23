#include "../../includes/main.h"

t_world *scene()
{
    static t_world *scene_ = NULL;

    if (!scene_)
    {
        scene_ = (t_world *)malloc(sizeof(t_world));
        if (!scene_)
            return (NULL);
        scene_->camera = NULL;
        scene_->lights_list = NULL;
        scene_->objects_list = NULL;
        scene_->ambient_list = NULL;

    }
    return (scene_);
}


void print_scene_data()
{
    t_world *world = scene();

    printf("Camera: %p\n", world->camera);
    printf("Lights: %p\n", world->lights_list);
    printf("Objects: %p\n", world->objects_list);
    printf("Ambient: %p\n", world->ambient_list);
}
