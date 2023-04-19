/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitpoint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:23:57 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 14:39:53 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	hit_wall(t_mlx *ptr, double xa, double ya, t_point *hit)
{
	int	x;
	int	y;

	x = qtc(hit->x);
	y = qtc(hit->y);
	while (y < (ptr->height) && y >= 0 && x < ptr->map_file[y]->len && x >= 0)
	{
		if (ptr->map[y][x] == '1')
			return ;
		hit->x += xa;
		hit->y += ya;
		x = qtc(hit->x);
		y = qtc(hit->y);
	}
}

void	find_tile_x(t_mlx *ptr, double angle)
{
	double	ya;
	double	xa;

	xa = TILE / tan(angle * M_PI / 180);
	ya = TILE;
	if (isperp(angle))
		xa = cos(angle * M_PI / 180) * TILE;
	if (isperp(angle) && (int)trunc(angle) % 180 == 0)
	{
		ptr->hit_x.valid = 0;
		return ;
	}
	if (sin(angle * M_PI / 180) > 0)
	{
		ptr->hit_x.y = qtc(ptr->pos.y) * TILE - 0.00001;
		ya *= -1;
	}
	else if (sin(angle * M_PI / 180) < 0)
	{
		ptr->hit_x.y = qtc(ptr->pos.y) * TILE + TILE;
		xa *= -1;
	}
	ptr->hit_x.x = ptr->pos.x + (ptr->pos.y - ptr->hit_x.y)
		/ tan(angle * M_PI / 180);
	hit_wall(ptr, xa, ya, &ptr->hit_x);
}

void	find_tile_y(t_mlx *ptr, double angle)
{
	double	xa;
	double	ya;

	ya = TILE * tan(angle * M_PI / 180);
	xa = TILE;
	if (isperp(angle))
		ya = sin(angle * M_PI / 180) * TILE;
	if (isperp(angle) && (int)trunc(angle) % 180 != 0)
	{
		ptr->hit_y.valid = 0;
		return ;
	}
	if (cos(angle * M_PI / 180) < 0)
	{
		ptr->hit_y.x = qtc(ptr->pos.x) * TILE -0.00001;
		xa *= -1;
	}
	else if (cos(angle * M_PI / 180) > 0)
	{
		ptr->hit_y.x = qtc(ptr->pos.x) * TILE + TILE;
		ya *= -1;
	}
	ptr->hit_y.y = ptr->pos.y + (ptr->pos.x - ptr->hit_y.x)
		* tan(angle * M_PI / 180);
	hit_wall(ptr, xa, ya, &ptr->hit_y);
}

double	offset(t_mlx *ptr, t_point hit, char axis, double distance)
{
	ptr->offset_y = (int) trunc(hit.y) % (int)TILE;
	ptr->offset_x = (int) trunc(hit.x) % (int)TILE;
	ptr->axis = axis;
	return (distance);
}

double	distance(t_mlx *ptr, double angle)
{
	double	a;
	double	b;

	if (isperp(angle))
	{
		a = sqrt(pow(ptr->pos.x - ptr->hit_y.x, 2)
				+ pow(ptr->pos.y - ptr->hit_y.y, 2));
		b = sqrt(pow(ptr->pos.x - ptr->hit_x.x, 2)
				+ pow(ptr->pos.y - ptr->hit_x.y, 2));
	}
	else
	{
		a = fabs((ptr->pos.y - ptr->hit_y.y) / sin(angle * M_PI / 180));
		b = fabs((ptr->pos.x - ptr->hit_x.x) / cos(angle * M_PI / 180));
	}
	if (ptr->hit_y.valid && (!ptr->hit_x.valid || a < b))
		return (offset(ptr, ptr->hit_y, 'y', a));
	return (offset(ptr, ptr->hit_x, 'x', b));
}
