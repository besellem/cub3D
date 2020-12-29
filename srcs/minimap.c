/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:58 by besellem          #+#    #+#             */
/*   Updated: 2020/12/29 01:03:33 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_ray(t_cub *cub, t_ray *ray)
{
	double distance;
	double xstep;
	double ystep;

	distance = ray->distance * cub->cub_size;
	while ((distance -= 5) > cub->cub_size / 2)
	{
		xstep = cos(ray->angle) * distance;
		ystep = sin(ray->angle) * distance;
		ft_pixel_put(cub,
					cub->pos_x * cub->cub_size + xstep,
					cub->pos_y * cub->cub_size + ystep,
					0xFFFFFF);
	}
}

/*
** PRINT PLAYER'S DOT
*/

void	print_player(t_cub *cub)
{
	int size;
	int i;
	int j;

	size = cub->cub_size / 2;
	i = -(size / 2);
	while (++i < size / 2)
	{
		j = -(size / 2);
		while (++j < size / 2)
			ft_pixel_put(cub, cub->pos_x * cub->cub_size + i,
						cub->pos_y * cub->cub_size + j, 0x808080);
	}
}

void	put_cub(t_cub *cub, int x, int y, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < cub->cub_size)
	{
		j = -1;
		while (++j < cub->cub_size)
		{
			ft_pixel_put(cub, x * cub->cub_size + i, y * cub->cub_size + j,
						color);
		}
	}
}

void	update_map(t_cub *cub)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < cub->map_size_y)
	{
		j = 0;
		while (j < cub->map_size_x)
		{
			if (cub->map[i][j] == '0' ||
				in_charset("NEWS", cub->map[i][j]) >= 0)
				put_cub(cub, j, i, UCOLOR_GREY);
			else if (cub->map[i][j] == '1')
				put_cub(cub, j, i, UCOLOR_BLACK);
			else if (cub->map[i][j] == '2')
				put_cub(cub, j, i, UCOLOR_BLUE);
			++j;
		}
		++i;
	}
}
