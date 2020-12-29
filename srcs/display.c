/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2020/12/29 00:56:22 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_cub *cub, int x, int y, unsigned int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

void	fill_background(t_cub *cub)
{
	int x;
	int y;

	x = -1;
	while (++x < cub->win_w)
	{
		y = 0;
		while (y < cub->win_h / 2)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
}
