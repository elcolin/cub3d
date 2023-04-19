/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:47:58 by elise             #+#    #+#             */
/*   Updated: 2023/03/09 15:45:44 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	solid_color(t_mlx *ptr, int size, int color, int start)
{
	int	i;
	int	j;

	i = start - 1;
	while (++i < size + start)
	{
		j = -1;
		while (++j < SCREENWIDTH)
			paint_pixel(ptr, j, i, color);
	}
}

int	create_img_addr(t_mlx *ptr, char *file_name, t_data *data)
{
	data->img = mlx_xpm_file_to_image(ptr->mlx_ptr, file_name,
			&data->width, &data->height);
	if (!data->img)
		return (0);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
	{
		mlx_destroy_image(ptr->mlx_ptr, data->img);
		data->img = 0;
		return (0);
	}
	return (1);
}

int	convert_color(char *s, t_mlx *ptr)
{
	int		j;
	char	*index;
	int		color[3];

	j = 0;
	index = s;
	isfunc(!(ft_strchr(index, ',')), empty_img, ptr, 1);
	while (j < 3)
	{
		color[j++] = ft_atoi(index);
		isfunc((color[j - 1] < 0 || color[j - 1] > 255), empty_img, ptr, 1);
		index = ft_strchr(index, ',');
		if (index && *index)
			index++;
	}
	return (create_trgb(0, color[0], color[1], color[2]));
}

void	img_creation(t_mlx *ptr, char **s, t_file *index)
{
	if (!(*s))
		isfunc(-1, empty_img, ptr, -1);
	if (ptr->img_tab[index->type - 1].img
		|| !create_img_addr(ptr, (*s), &ptr->img_tab[index->type - 1]))
	{
		free((*s));
		isfunc(-1, empty_img, ptr, -1);
	}
}

void	get_textures(t_mlx *ptr)
{
	int		i;
	t_file	*index;
	char	*s;

	i = 1;
	index = ptr->whole_file;
	while (index)
	{
		if (index->type && index->type < 5)
		{
			s = cut_outter(&index->s[3], ' ');
			img_creation(ptr, &s, index);
			free(s);
			i++;
		}
		else if (index->type > 4 && index->type < 7)
		{
			ptr->cf[index->type - 5] = convert_color(&index->s[2], ptr);
			i++;
		}
		index = index->next;
	}
	isfunc(i != 7, empty_img, ptr, 1);
}
