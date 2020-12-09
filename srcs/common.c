/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:45:35 by besellem          #+#    #+#             */
/*   Updated: 2020/12/10 00:10:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *err)
{
	write(2, "Error\n", 6);
	perror(err);
	exit(EXIT_FAILURE);
}

int		ft_strs_size(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		++i;
	return (i);
}

void	ft_free_strs(char **strs)
{
	int i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

int		is_rgb(int color)
{
	return (color >= 0 && color <= 255);
}

long	ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((long)(((r << 8) + g) << 8) + b);
}
