/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:03:02 by baouragh          #+#    #+#             */
/*   Updated: 2024/11/28 15:45:35 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RAY_H

#define RAY_H

#include "../vec3/vec3.h"

// To find a point of ray , you must use the equation of the ray: ___ P(t) = A + tB ___ where A is the origin of the ray, B is the direction of the ray and t is a scalar.

typedef struct s_ray
{
    t_point3    orig;
    t_vec3      dir;
}               t_ray;

t_ray create_ray(t_point3 orig, t_vec3 dir);
t_vec3 ray_at(t_ray ray, double t);


#endif