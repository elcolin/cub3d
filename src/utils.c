/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:06:35 by ecolin            #+#    #+#             */
/*   Updated: 2023/03/08 18:17:31 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	qtc(double a)
{
	return (trunc(a / TILE));
}

int	isperp(double angle)
{
	if (angle == 180 || angle == 90 || angle == 270 || angle == 0
		|| angle == -90 || angle == -270 || angle == -180 || angle == -0)
		return (1);
	return (0);
}

int	end_all( t_mlx *ptr)
{
	exit(empty_img(ptr));
}

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	sig;

	i = 0;
	res = 0;
	sig = 1;
	if (!s || !ft_isdigit(s[0]) || !s[0])
		return (-1);
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sig *= -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res *= 10;
		res += s[i] - 48;
		i++;
	}
	if (s[i] != '\0' && s[i] != ',')
		return (-1);
	return (res * sig);
}

char	*cut_outter(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = 0;
	k = 0;
	copy = NULL;
	if (!s || !s[0])
		return (0);
	j = ft_strlen(s);
	while (s[i] == c)
		i++;
	while (s[j - 1] == c)
		j--;
	if ((j - i + 1) > 0)
		copy = malloc(j - i + 1);
	if (!copy)
		return (NULL);
	copy[j - i] = 0;
	while (i < j)
		copy[k++] = s[i++];
	return (copy);
}
