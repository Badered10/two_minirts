/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:18:48 by baouragh          #+#    #+#             */
/*   Updated: 2024/11/24 15:02:32 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    free_all(t_infos *infos, char *msg, unsigned int ex_s)
{
    ft_lstclear(&infos->garbage, &free);
    print_err(msg);
    exit (ex_s);
}
