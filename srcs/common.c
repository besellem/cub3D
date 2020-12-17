/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:45:35 by besellem          #+#    #+#             */
/*   Updated: 2020/12/17 02:12:04 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *err, t_cub *cub, char *file, int line)
{
	if (cub)
		ft_free_cub(cub);
	ft_putendl_fd(CUB_ERR, 2);
	if (file && line > 0)
		ft_dprintf(2, B_YELLOW"%s:%d: "CLR_COLOR, file, line);
	ft_putendl_fd(err, 2);
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
