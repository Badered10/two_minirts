/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:34:28 by baouragh          #+#    #+#             */
/*   Updated: 2024/12/19 15:41:01 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3 vec3(double x, double y, double z)
{
    t_vec3 v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3 v;

    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;

    return (v);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    t_vec3 v;

    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;

    return (v);
}

t_vec3 vec3_mul(t_vec3 a, t_vec3 b)
{
    t_vec3 v;

    v.x = a.x * b.x;
    v.y = a.y * b.y;
    v.z = a.z * b.z;

    return (v);
}

t_vec3 vec3_div(t_vec3 a, t_vec3 b)
{
    t_vec3 v;

    v.x = a.x / b.x;
    v.y = a.y / b.y;
    v.z = a.z / b.z;

    return (v);
}

t_vec3 vec3_scale(t_vec3 a, double t)
{
    t_vec3 v;

    v.x = a.x * t;
    v.y = a.y * t;
    v.z = a.z * t;

    return (v);
}

double vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 v;

    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;

    return (v);
}

double vec3_length(t_vec3 a)
{
    return (sqrt(vec3_dot(a, a)));
}

t_vec3 vec3_unit(t_vec3 a)
{
    return (vec3_scale(a, 1 / vec3_length(a)));
}

t_point3 create_point3(double x, double y, double z)
{
    return ((t_point3)vec3(x, y, z));
}
