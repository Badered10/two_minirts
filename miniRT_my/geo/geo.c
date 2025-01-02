#include "geo.h"

// DEBUG FUNCTION-------------------------------------------------------------------------------
void print_type(t_tuple *tuple)
{
    if (tuple->w == 0)
        printf("is Vector : x = %f, y = %f, z = %f, w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else if (tuple->w == 1)
        printf("is Point : x = %f, y = %f, z = %f , w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
    else
        printf("is Undefined : x = %f, y = %f, z = %f , w = %d\n",
            tuple->x, tuple->y, tuple->z, tuple->w);
}

// CREATE A TUPLE STRUCTURE---------------------------------------------------------------------
t_tuple *creat_tuple(double x, double y, double z, double w)
{
    t_tuple *tuple =(t_tuple *)malloc(sizeof(t_tuple));
    if (tuple == NULL)
        return (NULL);

    tuple->x = x;
    tuple->y = y;
    tuple->z = z;
    tuple->w = w;

    return (tuple);
}

t_tuple *creat_point(double x, double y, double z)
{
    return (creat_tuple(x, y, z, 1));
}

t_tuple *creat_vector(double x, double y, double z)
{
    return (creat_tuple(x, y, z, 0));
}

// ARTHEMATIC FUNCTIONS-------------------------------------------------------------------------

bool equal(double a, double b)
{
    if (fabs(a - b) < EPSILON)
        return (true);
    else
        return (false);
}

bool equal_tuple(t_tuple *a, t_tuple *b)
{
    if (equal(a->x, b->x) && equal(a->y, b->y) && equal(a->z, b->z) && a->w == b->w)
        return (true);
    else
        return (false);
}

t_tuple *add_tuple(t_tuple *a, t_tuple *b)
{
    return (creat_tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w));
}

t_tuple *sub_tuple(t_tuple *a, t_tuple *b)
{
    return (creat_tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w));
}

t_tuple *negate_tuple(t_tuple *a)
{
    return (creat_tuple(-a->x, -a->y, -a->z, -a->w));
}

t_tuple *mul_tuple(t_tuple *a, double b)
{
    return (creat_tuple(a->x * b, a->y * b, a->z * b, a->w * b));
}

t_tuple *div_tuple(t_tuple *a, double b)
{
    return (creat_tuple(a->x / b, a->y / b, a->z / b, a->w / b));
}
double len_tuple(t_tuple *a)
{
    return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}
t_tuple *norm_tuple(t_tuple *a)
{
    return (div_tuple(a, len_tuple(a)));
}

double dot_tuple(t_tuple *a, t_tuple *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_tuple *cross_tuple(t_tuple *a, t_tuple *b)
{
    return (creat_vector(a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x));
}
// MAIN FUNCTION--------------------------------------------------------------------------------

typedef struct projectile
{
    t_tuple *position;
    t_tuple *velocity;
} t_projectile;

typedef struct environment
{
    t_tuple *gravity;
    t_tuple *wind;
} t_environment;


t_projectile *creat_projectile(t_tuple *position, t_tuple *velocity)
{
    t_projectile *projectile = (t_projectile *)malloc(sizeof(t_projectile));
    if (projectile == NULL)
        return (NULL);

    projectile->position = position;
    projectile->velocity = velocity;

    return (projectile);
}

t_environment *creat_environment(t_tuple *gravity, t_tuple *wind)
{
    t_environment *environment = (t_environment *)malloc(sizeof(t_environment));
    if (environment == NULL)
        return (NULL);

    environment->gravity = gravity;
    environment->wind = wind;

    return (environment);
}

t_projectile *tick(t_environment *env, t_projectile *projectile)
{
    t_tuple *position = add_tuple(projectile->position, projectile->velocity);
    t_tuple *velocity = add_tuple(add_tuple(projectile->velocity, env->gravity), env->wind);

    return (creat_projectile(position, velocity));
}


int main()
{
    t_projectile *projectile = creat_projectile()
    return (0);
}