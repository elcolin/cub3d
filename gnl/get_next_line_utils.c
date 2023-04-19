/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:20:38 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/09 15:04:30 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize < 1)
		return (0);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!*s || c < 0)
		return (0);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	cpy = malloc(i + 1);
	if (!cpy)
		return (0);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = s[i];
	return (cpy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*s;

	i = ft_strlen(s1);
	size = i + ft_strlen(s2) + 1;
	s = malloc(size);
	if (!s)
		return (0);
	ft_strlcpy(s, s1, size);
	ft_strlcpy(s + i, s2, size);
	return (s);
}
