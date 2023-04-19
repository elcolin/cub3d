/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:52:06 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 16:01:46 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	isfunc(int f, int (*l)(), void *param, int err)
{
	if (f == err)
	{
		if (l)
			(*l)(param);
		printf("Ohoh! Error occurred\n");
		exit(EXIT_FAILURE);
	}
}

int	empty_mlx(t_mlx *ptr)
{
	mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
	mlx_destroy_display(ptr->mlx_ptr);
	free(ptr->mlx_ptr);
	return (1);
}

int	empty_file(t_mlx *ptr)
{
	t_file	*index;
	t_file	*tmp;

	index = ptr->whole_file;
	while (index)
	{
		if (index->s)
			free(index->s);
		tmp = index->next;
		free(index);
		index = tmp;
	}
	empty_mlx(ptr);
	return (1);
}

int	empty_map(t_mlx *ptr)
{
	empty_file(ptr);
	free(ptr->map);
	free(ptr->map_file);
	return (1);
}

int	empty_img(t_mlx *ptr)
{
	int	i;

	i = 0;
	if (ptr->tmp.img)
		mlx_destroy_image(ptr->mlx_ptr, ptr->tmp.img);
	while (i < 4)
	{
		if (ptr->img_tab[i].img)
			mlx_destroy_image(ptr->mlx_ptr, ptr->img_tab[i].img);
		ptr->img_tab[i++].img = 0;
	}
	empty_map(ptr);
	return (1);
}
