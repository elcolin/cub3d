/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:16:15 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/09 16:04:55 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/stat.h>
# include <fcntl.h>
# include "../gnl/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# include <limits.h>

# define ALPHA 10
# define FOV 55.0
# define TILE 64.0 
# define SCREENHEIGHT 800.0
# define SCREENWIDTH 1280.0
# define MAPHEIGHT 40
# define MAPWIDTH 65

enum e_texture{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	F = 5,
	C = 6,
	MAP = 7
};

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_point {
	double	x;
	double	y;
	int		valid;
}	t_point;

typedef struct s_entity {
	int		x;
	int		y;
	int		type;
	double	angle;
}	t_entity;

typedef struct s_file
{
	int				id;
	char			*s;
	int				len;
	int				type;
	struct s_file	*next;
	struct s_file	*prev;

}	t_file;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			height;
	int			width;
	int			key_dis;

	int			cf[2];
	t_data		img_tab[4];
	t_data		tmp;
	int			offset_x;
	int			offset_y;
	int			color;

	t_entity	player;
	t_point		pos;
	t_point		hit_x;
	t_point		hit_y;
	char		axis;

	t_file		*whole_file;
	t_file		**map_file;
	int			file_height;
}	t_mlx;

int		create_trgb(int t, int r, int g, int b);
void	find_tile_y(t_mlx *ptr, double angle);
void	find_tile_x(t_mlx *ptr, double angle);
void	print_line(t_mlx *ptr, double wall_dist, int col);
double	distance(t_mlx *ptr, double angle);
void	what_color(t_mlx *ptr);
void	print_fov(t_mlx *ptr);
void	test_ceiling_floor(t_mlx *ptr);
void	isfunc(int f, int (*l)(), void *param, int err);
void	create_map(t_mlx *ptr);
int		malloc_map(char *filename, t_mlx *ptr);
void	get_size_file(t_mlx *ptr, char *argv);
int		is_mapline(t_file *s);
int		get_map(t_mlx *ptr, t_file *start);
char	*ft_strstr(char *hatch, char *little);
int		qtc(double a);
char	*cut_outter(char *s, char c);
int		ft_isdigit(int c);
int		ft_atoi(char *s);
void	solid_color(t_mlx *ptr, int size, int color, int start);
int		is_null(void *ptr);
int		empty_mlx(t_mlx *ptr);
int		empty_file(t_mlx *ptr);
int		empty_map(t_mlx *ptr);
int		empty_img(t_mlx *ptr);
void	get_textures(t_mlx *ptr);
int		isperp(double angle);
int		end_all( t_mlx *ptr);
t_file	*new_line(char *s, int id, int type, t_file *prev);
void	paint_pixel(t_mlx *ptr, int x, int y, int color);

#endif