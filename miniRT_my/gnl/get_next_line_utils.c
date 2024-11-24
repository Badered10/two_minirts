/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:26:03 by baouragh          #+#    #+#             */
/*   Updated: 2024/10/31 18:15:43 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	unsigned char	*destination;
	unsigned char	*source;

	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!src && !dst)
		return (NULL);
	if (src > dst)
	{
		if (!destination && !source)
			return (NULL);
		if (destination == source)
			return (dst);
		while (len--)
			*destination++ = *source++;
		return (dst);
	}
	while (len != 0)
	{
		destination[len - 1] = source[len - 1];
		len--;
	}
	return ((void *)destination);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*copy;
	size_t	lenth;

	if (!s1)
		return (ft_strdup_gnl(""));
	lenth = ft_strlen_gnl(s1);
	copy = (char *)malloc(lenth + 1);
	if (!copy)
		return (NULL);
	ft_memmove_gnl(copy, s1, lenth);
	copy[lenth] = '\0';
	return (copy);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;

	if (!s1 && !s2)
		return (ft_strdup_gnl(""));
	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	new = (char *)malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1);
	if (!new)
		return (NULL);
	ft_memmove_gnl(new, s1, ft_strlen_gnl(s1));
	ft_memmove_gnl(new + ft_strlen_gnl(s1), s2, ft_strlen_gnl(s2));
	new[ft_strlen_gnl(s1) + ft_strlen_gnl(s2)] = '\0';
	return (new);
}
