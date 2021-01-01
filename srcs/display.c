/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2020/12/31 19:22:08 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_pixel_put(t_cub *cub, int x, int y, unsigned int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

void		fill_background(t_cub *cub)
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

static void	print_texture_ray(t_cub *cub, t_img *tx, int idx, double size)
{
	char	*px;
	int		i;
	int		j;

	i = -1;
	while (++i < tx->y / 2)
	{
		j = -1;
		while (++j < tx->x)
		{
			px = tx->addr + (i * tx->size_line + j * (tx->bits_per_pixel / 8));
			ft_pixel_put(cub, j, i, *(unsigned int *)px);
		}
	}
	(void)size;
	(void)idx;
	/*
	i = -1;
	while (++i < size)
	{
		px = tx->addr + (idx * tx->size_line + i * (tx->bits_per_pixel / 8));
		ft_pixel_put(cub, idx, ((cub->win_h - size) / 2) + i, *(unsigned int *)px);
	}
	*/
}

void		update_cubs(t_cub *cub)
{
	double	ratio;
	int		x;
	int		tmp;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
		if (ratio < 1)
			ratio = cub->win_h;
		else
			ratio = cub->win_h / ratio;
		tmp = (cub->win_h - ratio) / 2;

		if (cub->rays[x].hit_vertical && cub->rays[x].is_right)			// EAST (RIGHT) TEXTURE
			print_texture_ray(cub, &(cub->txtrs[2]), x, ratio);
		else if (cub->rays[x].hit_vertical && !cub->rays[x].is_right)	// WEST (LEFT) TEXTURE
			print_texture_ray(cub, &(cub->txtrs[3]), x, ratio);
		else if (!cub->rays[x].hit_vertical && cub->rays[x].is_down)	// SOUTH (DOWN) TEXTURE
			print_texture_ray(cub, &(cub->txtrs[1]), x, ratio);
		else if (!cub->rays[x].hit_vertical && !cub->rays[x].is_down)	// NORTH (UP) TEXTURE
			print_texture_ray(cub, &(cub->txtrs[0]), x, ratio);
	}
}
