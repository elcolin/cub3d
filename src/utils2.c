/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:13:15 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 18:17:25 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	paint_pixel(t_mlx *ptr, int x, int y, int color)
{
	int	pixel;

	pixel = (y * ptr->tmp.line_length) + (x * 4);
	if (x < 0 || y < 0 || pixel < 0 || y >= SCREENHEIGHT || x >= SCREENWIDTH)
		return ;
	if (ptr->tmp.endian == 1)
	{
		ptr->tmp.addr[pixel + 0] = (color >> 24);
		ptr->tmp.addr[pixel + 1] = (color >> 16) & 0xFF;
		ptr->tmp.addr[pixel + 2] = (color >> 8) & 0xFF;
		ptr->tmp.addr[pixel + 3] = (color) & 0xFF;
	}
	else if (ptr->tmp.endian == 0)
	{
		ptr->tmp.addr[pixel + 0] = (color) & 0xFF;
		ptr->tmp.addr[pixel + 1] = (color >> 8) & 0xFF;
		ptr->tmp.addr[pixel + 2] = (color >> 16) & 0xFF;
		ptr->tmp.addr[pixel + 3] = (color >> 24);
	}
}
