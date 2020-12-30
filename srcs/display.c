/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2020/12/30 23:45:46 by besellem         ###   ########.fr       */
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
	// char	*px;
	int		x;
	int		y;
	int		color;
	int		tmp;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
		ratio = cub->win_h / (ratio < 1 ? 1 : ratio);
		tmp = (cub->win_h - ratio) / 2;
		/*
		px = cub->txtrs[3].addr + (0 * cub->txtrs[3].size_line + 0 * (cub->txtrs[3].bits_per_pixel / 8));
		*/
		if (cub->rays[x].hit_vertical && cub->rays[x].is_right)
		{
			// EAST (RIGHT) TEXTURE
			color = UCOLOR_GREY;
		}
		else if (cub->rays[x].hit_vertical && !cub->rays[x].is_right)
		{
			// WEST (LEFT) TEXTURE
			color = UCOLOR_BLACK;
		}
		else if (!cub->rays[x].hit_vertical && cub->rays[x].is_down)
		{
			// SOUTH (DOWN) TEXTURE
			color = UCOLOR_BLUE;
		}
		else if (!cub->rays[x].hit_vertical && !cub->rays[x].is_down)
		{
			// NORTH (UP) TEXTURE
			color = UCOLOR_RED;
		}
		y = -1;
		while (++y < ratio)
		{
			// ft_pixel_put(cub, x, tmp + y, *(unsigned int *)px);
			ft_pixel_put(cub, x, tmp + y, color);
		}
	}
}
