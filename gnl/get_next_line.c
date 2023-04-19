/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:56:00 by ecolin            #+#    #+#             */
/*   Updated: 2023/01/23 18:58:45 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *) s + i) = 0;
		i++;
	}
}

char	*untilnewline(int fd, char *stash)
{
	int		ret;
	char	*temp;
	char	*res;
	char	buf[BUFFER_SIZE + 1];

	ret = BUFFER_SIZE;
	temp = 0;
	res = ft_strdup(stash);
	while (!ft_strchr(res, '\n') && ret == BUFFER_SIZE)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (!ret)
			return (res);
		else if (ret == -1)
		{
			free(res);
			return (NULL);
		}
		buf[ret] = '\0';
		temp = ft_strjoin(res, buf);
		free(res);
		res = ft_strdup(temp);
		free(temp);
	}
	return (res);
}

char	*makestash(char *l, char *stash)
{
	if (l && *(l + 1))
	{
		ft_strlcpy(stash, l + 1, BUFFER_SIZE + 1);
		*(l + 1) = '\0';
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*res;
	int			ret;

	ret = 0;
	res = 0;
	if (!stash[0])
	{
		ret = read(fd, stash, BUFFER_SIZE);
		if (ret == -1 || !ret)
			return (NULL);
		stash[ret] = '\0';
	}
	res = untilnewline(fd, stash);
	if (!res)
		return (NULL);
	ft_bzero(stash, BUFFER_SIZE + 1);
	makestash(ft_strchr(res, '\n'), stash);
	return (res);
}
