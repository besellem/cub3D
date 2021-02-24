/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:58 by besellem          #+#    #+#             */
/*   Updated: 2021/02/24 10:24:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_ray(t_cub *cub, t_ray *ray)
{
	double distance;

	distance = ray->distance * cub->cub_size;
	while ((distance -= 1) > 0)
	{
		ft_pixel_put(cub,
					cub->pos_x * cub->cub_size + cos(ray->angle) * distance,
					cub->pos_y * cub->cub_size + sin(ray->angle) * distance,
					0xFFFFFF);
	}
}

/*
** PRINT PLAYER'S DOT
*/

static void	print_player(t_cub *cub)
{
	int size;
	int i;
	int j;

	size = cub->cub_size;
	i = -(size / 2);
	while (++i < size / 2)
	{
		j = -(size / 2);
		while (++j < size / 2)
		{
			ft_pixel_put(cub, cub->pos_x * cub->cub_size + i,
						cub->pos_y * cub->cub_size + j, 0x808080);
		}
	}
}

static void	put_cub(t_cub *cub, int x, int y, uint32_t color)
{
	int i;
	int j;

	i = -1;
	while (++i < cub->cub_size)
	{
		j = -1;
		while (++j < cub->cub_size)
			ft_pixel_put(cub, x * cub->cub_size + i, y * cub->cub_size + j,
						color);
	}
}

static void	put_map(t_cub *cub)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < cub->map_size_y)
	{
		j = 0;
		while (j < cub->map_size_x)
		{
			if (cub->map[i][j] != '1' && cub->map[i][j] != ' ')
				put_cub(cub, j, i, UCOLOR_GREY);
			else if (cub->map[i][j] == '1')
				put_cub(cub, j, i, UCOLOR_BLACK);
			++j;
		}
		++i;
	}
}

void		update_minimap(t_cub *cub)
{
	int i;

	put_map(cub);
	i = -1;
	while (++i < cub->win_w)
		print_ray(cub, &(cub->rays[i]));


	// TO DEBUG SPRITE'S RAYCASTING
	int j;

	i = 0;
	while ((size_t)i < cub->map_size_y)
	{
		j = 0;
		while ((size_t)j < cub->map_size_x)
		{
			if (is_sprite(cub->map[i][j]) &&
				cub->sprites[get_sprite_idx(cub, j, i)].hit == 1)
			{
				put_cub(cub, j, i, UCOLOR_RED);
			}
			++j;
		}
		++i;
	}
	// END


	print_player(cub);
}
