/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2020/12/29 22:24:57 by besellem         ###   ########.fr       */
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

void	update_cubs(t_cub *cub)
{
	double	ratio;
	int		x;
	int		y;
	int		color;
	int		tmp;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
		ratio = cub->win_h / (ratio < 1 ? 1 : ratio);
		tmp = (int)((cub->win_h - ratio) / 2);
		color = UCOLOR_GREY;
		/*
		if (cub->rays[x].hit_vertical && cub->rays[x].is_right)
			color = 0xff08e2;
		else if (cub->rays[x].hit_vertical && !cub->rays[x].is_right)
			color = 0x0008e2;
		else if (!cub->rays[x].hit_vertical && cub->rays[x].is_right)
			color = 0xe208ff;
		else if (!cub->rays[x].hit_vertical && !cub->rays[x].is_right)
			color = 0xffd2ff;
		*/
		y = -1;
		while (++y < ratio)
		{
			ft_pixel_put(cub, x, tmp + y, color);
		}
	}
}
