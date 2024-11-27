/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:25 by baouragh          #+#    #+#             */
/*   Updated: 2024/11/27 15:35:27 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
#define VECTOR3_H


#include <math.h>

typedef struct s_vec3
{
    double x;
    double y;
    double z;
}               t_vec3;

t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, t_vec3 b);
t_vec3 vec3_div(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 a, double t);
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
double vec3_length(t_vec3 a);
t_vec3 vec3_unit(t_vec3 a);

#endif