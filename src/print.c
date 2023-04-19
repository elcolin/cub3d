/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:11:41 by elise             #+#    #+#             */
/*   Updated: 2023/03/08 18:15:53 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	what_color(t_mlx *ptr)
{
	static int	type;

	if (((type == SO && (ptr->offset_y)) || (type == EA && ptr->offset_x)
			|| (type == WE && ptr->offset_x != 63)
			|| (type == NO && ptr->offset_y != 63)))
		type = 0;
	if (((type == SO || type == NO) && ptr->axis == 'y')
		|| ((type == EA || type == WE) && ptr->axis == 'x'))
		type = 0;
	else if (type)
		return ;
	if (!ptr->offset_y && ptr->axis == 'x')
		type = SO;
	else if (!ptr->offset_x && ptr->axis == 'y')
		type = EA;
	else if (ptr->offset_x == 63 && ptr->axis == 'y')
		type = WE;
	else if (ptr->offset_y == 63 && ptr->axis == 'x')
		type = NO;
	ptr->color = type;
}

int	my_mlx_pixel_put(t_data *data, int x, int y)
{
	char	*dst;
	int		*test;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	test = (int *) dst;
	return (*test);
}

void	print_line(t_mlx *ptr, double wall_dist, int col)
{
	double		proj_height;
	double		a;
	static int	val;

	if (!wall_dist)
		return ;
	if (!val)
		val = ((double)(SCREENWIDTH / 2) / tan((FOV / 2) * M_PI / 180));
	what_color(ptr);
	a = 0;
	proj_height = (double) ceil(TILE / wall_dist * val);
	while (a < proj_height)
	{
		if (ptr->color == WE || ptr->color == EA)
			paint_pixel(ptr, SCREENWIDTH - col, SCREENHEIGHT / 2 - proj_height
				/ 2 + a, my_mlx_pixel_put(&ptr->img_tab[ptr->color - 1],
					ptr->offset_y, trunc(a * TILE / (proj_height))));
		else if (ptr->color == NO || ptr->color == SO)
			paint_pixel(ptr, SCREENWIDTH - col, SCREENHEIGHT / 2 - proj_height
				/ 2 + a, my_mlx_pixel_put(&ptr->img_tab[ptr->color - 1],
					ptr->offset_x, trunc(a * TILE / (proj_height))));
		a++;
	}
}

void	print_fov(t_mlx *ptr)
{
	double	angle;
	int		i;

	i = 0;
	angle = ptr->player.angle - FOV / 2;
	if (ptr->tmp.addr == NULL)
	{
		ptr->tmp.img = mlx_new_image(ptr->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
		ptr->tmp.addr = mlx_get_data_addr(ptr->tmp.img,
				&ptr->tmp.bits_per_pixel,
				&ptr->tmp.line_length, &ptr->tmp.endian);
	}
	solid_color(ptr, SCREENHEIGHT / 2, ptr->cf[1], 0);
	solid_color(ptr, SCREENHEIGHT / 2, ptr->cf[0], SCREENHEIGHT / 2);
	while (angle <= ptr->player.angle + FOV / 2 && i <= SCREENWIDTH)
	{
		ptr->hit_x.valid = 1;
		ptr->hit_y.valid = 1;
		find_tile_x(ptr, angle);
		find_tile_y(ptr, angle);
		print_line(ptr, distance(ptr, angle)
			* cos((angle - ptr->player.angle) * M_PI / 180), i++);
		angle += (double) FOV / SCREENWIDTH;
	}
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->tmp.img, 0, 0);
}
