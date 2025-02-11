/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:26:03 by baouragh          #+#    #+#             */
/*   Updated: 2025/02/11 05:28:12 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*gft_memmove(void *dst, const void *src, size_t len)
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

char	*gft_strdup(char *s1)
{
	char	*copy;
	size_t	lenth;

	if (!s1)
		return (gft_strdup(""));
	lenth = gft_strlen(s1);
	copy = (char *)malloc(lenth + 1);
	if (!copy)
		return (NULL);
	gft_memmove(copy, s1, lenth);
	copy[lenth] = '\0';
	return (copy);
}

char	*gft_strjoin(char *s1, char *s2)
{
	char	*new;

	if (!s1 && !s2)
		return (gft_strdup(""));
	if (!s1)
		return (gft_strdup(s2));
	if (!s2)
		return (gft_strdup(s1));
	new = (char *)malloc((gft_strlen(s1) + gft_strlen(s2)) + 1);
	if (!new)
		return (NULL);
	gft_memmove(new, s1, gft_strlen(s1));
	gft_memmove(new + gft_strlen(s1), s2, gft_strlen(s2));
	new[gft_strlen(s1) + gft_strlen(s2)] = '\0';
	return (new);
}
