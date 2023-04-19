/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:39:38 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 18:11:16 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map(t_mlx *ptr, t_file *start)
{
	t_file	*fmap;
	int		i;

	i = 0;
	fmap = start;
	ptr->height = ptr->file_height - fmap->id;
	ptr->map = malloc((ptr->height + 1) * sizeof(char *));
	isfunc(!(ptr->map), empty_file, ptr, 1);
	ptr->map_file = malloc((ptr->height + 1) * sizeof(t_file *));
	if (!ptr->map_file)
	{
		free(ptr->map);
		isfunc(!(ptr->map_file), empty_file, ptr, 1);
	}
	while (fmap)
	{
		ptr->map_file[i] = fmap;
		ptr->map[i++] = fmap->s;
		fmap = fmap->next;
	}
	ptr->map[ptr->height] = 0;
	ptr->map_file[ptr->height] = 0;
	return (1);
}

void	got_player(t_mlx *ptr, int y, char c)
{
	isfunc(ptr->player.y != -1 || ft_strchr(ft_strchr(ptr->map[y], c) + 1, c),
		empty_map, ptr, 1);
	if (c == 'N')
		ptr->player.angle = 90;
	else if (c == 'E')
		ptr->player.angle = 0;
	else if (c == 'W')
		ptr->player.angle = 180;
	else if (c == 'S')
		ptr->player.angle = 270;
	ptr->player.y = y;
	ptr->player.x = ft_strchr(ptr->map[y], c) - (&ptr->map[y][0]);
	ptr->pos.y = y * TILE + TILE / 2;
	ptr->pos.x = ptr->player.x * TILE + TILE / 2;
}

int	is_mapline(t_file *s)
{
	int	i;

	i = 0;
	while (s->s[i] != '\0')
	{
		if (s->s[i] != ' ' && s->s[i] != '0' && s->s[i] != '1' && s->s[i] != 'N'
			&& s->s[i] != 'S' && s->s[i] != 'E' && s->s[i] != 'W')
			return (-1);
		if ((ft_strchr("NSEW0", s->s[i]) && i == 0)
			|| (i && ft_strchr("NSEW0", s->s[i])
				&& s->s[i - 1] == ' ') || ((s->s[i + 1] == ' '
					|| s->s[i + 1] == '\0')
				&& ft_strchr("NSEW0", s->s[i])))
			return (-1);
		if (ft_strchr("NSEW0", s->s[i]) && ((s->prev && s->prev->len <= i)
				|| (s->next && s->next->len <= i) || ((!s->prev || !s->next))
				|| ((s->prev && i < s->prev->len && (s->prev->s[i] == ' '
							|| s->prev->s[i] == '\0'))
					|| (s->next && i < s->next->len && (s->next->s[i] == ' '
							|| s->next->s[i] == '\0')))))
			return (-1);
		++i;
	}
	return (1);
}

void	create_map(t_mlx *ptr)
{
	int		i;

	i = 0;
	while (ptr->map_file[i])
	{
		isfunc(is_mapline(ptr->map_file[i]), empty_map, ptr, -1);
		if (ft_strchr(ptr->map[i], 'N'))
			got_player(ptr, i, 'N');
		if (ft_strchr(ptr->map[i], 'E'))
			got_player(ptr, i, 'E');
		if (ft_strchr(ptr->map[i], 'W'))
			got_player(ptr, i, 'W');
		if (ft_strchr(ptr->map[i], 'S'))
			got_player(ptr, i, 'S');
		++i;
	}
	isfunc(ptr->player.y == -1 || ptr->player.x == -1, empty_map, ptr, 1);
}
