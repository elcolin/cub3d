/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:13:30 by elise             #+#    #+#             */
/*   Updated: 2023/03/08 18:11:23 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	*new_line(char *s, int id, int type, t_file *prev)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
	{
		free(s);
		return (0);
	}
	new->id = id;
	new->len = ft_strlen(s);
	new->s = s;
	new->next = 0;
	new->type = type;
	new->prev = prev;
	return (new);
}

char	*int_totype(int type)
{
	if (type == NO)
		return ("NO ");
	else if (type == SO)
		return ("SO ");
	else if (type == WE)
		return ("WE ");
	else if (type == EA)
		return ("EA ");
	else if (type == F)
		return ("F ");
	else if (type == C)
		return ("C ");
	else if (type == MAP)
		return ("1");
	return (0);
}

int	type(char *s)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (ft_strstr(s, int_totype(i)) == s
			|| (ft_strstr(s, int_totype(i)) && i == 7))
			return (i);
		i++;
	}
	return (0);
}

void	get_size_file(t_mlx *ptr, char *argv)
{
	int		fd;
	char	*str;
	int		i;
	t_file	*file;

	i = 0;
	isfunc(fd = open(argv, O_RDONLY), empty_mlx, ptr, -1);
	isfunc(!(str = get_next_line(fd)), empty_mlx, ptr, 1);
	if (ft_strchr(str, '\n'))
		*ft_strchr(str, '\n') = '\0';
	ptr->whole_file = new_line(str, i, type(str), 0);
	isfunc(!(ptr->whole_file), empty_mlx, ptr, 1);
	file = ptr->whole_file;
	str = get_next_line(fd);
	while (str)
	{
		if (ft_strchr(str, '\n'))
			*ft_strchr(str, '\n') = '\0';
		file->next = new_line(str, ++i, type(str), file);
		isfunc(!(file->next), empty_file, ptr, 1);
		file = file->next;
		str = get_next_line(fd);
	}
	ptr->file_height = i + 1;
	isfunc(close(fd), empty_file, ptr, -1);
}

char	*ft_strstr(char *hatch, char *little)
{
	int	i;
	int	j;

	i = 0;
	if (!hatch)
		return (0);
	while (hatch[i])
	{
		j = 0;
		while (hatch[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return (&hatch[i]);
		}
		i++;
	}
	return (0);
}
