/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:02:12 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 18:34:41 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotation(t_mlx *ptr, int key)
{
	if (key != 65361 && key != 65363)
		return (0);
	if (key == 65361)
		ptr->player.angle += ALPHA;
	else
		ptr->player.angle -= ALPHA;
	if (ptr->player.angle >= 360 || ptr->player.angle <= -360)
		ptr->player.angle = 0;
	print_fov(ptr);
	return (1);
}

int	movement(t_mlx *ptr, double x, double y, int key)
{
	if (key == 'w' || key == 's')
	{
		x *= cos(ptr->player.angle * M_PI / 180) * 31;
		y *= sin(ptr->player.angle * M_PI / 180) * (-1) * 31;
	}
	else if (key == 'a' || key == 'd')
	{
		y *= cos(ptr->player.angle * M_PI / 180) * 31 ;
		x *= sin(ptr->player.angle * M_PI / 180) * (-1) * 31;
	}
	else
		return (0);
	if (ft_strchr("NS0WEP", ptr->map[qtc(ptr->pos.y + y)][qtc(ptr->pos.x + x)]))
	{
		ptr->map[ptr->player.y][ptr->player.x] = '0';
		ptr->pos.x = ptr->pos.x + x;
		ptr->pos.y = ptr->pos.y + y;
		ptr->player.x = qtc(ptr->pos.x);
		ptr->player.y = qtc(ptr->pos.y);
		ptr->map[ptr->player.y][ptr->player.x] = 'P';
		print_fov(ptr);
		return (1);
	}
	return (0);
}

int	key_hooked(int key, t_mlx *ptr)
{
	if (key == 65307)
		exit(empty_img(ptr));
	if (rotation(ptr, key))
		return (1);
	if (key == 119 || key == 'w')
		movement(ptr, 1, 1, key);
	else if (key == 115 || key == 's')
		movement(ptr, -1, -1, key);
	else if (key == 2 || key == 'd')
		movement(ptr, -1, 1, key);
	else if (key == 0 || key == 'a')
		movement(ptr, 1, -1, key);
	return (1);
}

void	init_mlx(t_mlx *ptr)
{
	int	i;

	i = 0;
	while (i < 4)
		ptr->img_tab[i++].img = 0;
	ptr->player.x = -1;
	ptr->player.y = -1;
	ptr->pos.x = -1;
	ptr->pos.y = -1;
	ptr->key_dis = 0;
	ptr->tmp.img = 0;
	ptr->tmp.addr = 0;
	ptr->mlx_ptr = mlx_init();
	isfunc(!(ptr->mlx_ptr), 0, 0, 1);
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, SCREENWIDTH,
			SCREENHEIGHT, "cub3d");
	isfunc(!(ptr->win_ptr), mlx_destroy_display, ptr->mlx_ptr, 1);
	ptr->map = 0;
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_file	*index;

	isfunc(argc != 2, 0, 0, 1);
	init_mlx(&mlx);
	get_size_file(&mlx, argv[1]);
	index = mlx.whole_file;
	while (index && index->type != MAP)
		index = index->next;
	isfunc(!index, empty_file, &mlx, 1);
	get_map(&mlx, index);
	create_map(&mlx);
	get_textures(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_hooked, &mlx);
	mlx_hook(mlx.win_ptr, 33, 1L >> 2, end_all, &mlx);
	print_fov(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
