/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/01/25 15:08:39 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}

static int	get_sprite_idx(t_cub *cub, int x, int y)
{
	int i;

	i = 0;
	while (i < cub->sp_ocs - 1)
	{
		if (cub->sprites[i].x == x && cub->sprites[i].y == y)
			break ;
		++i;
	}
	return (i);
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	t_uint32	*ptr;
	int			idx;
	int			i;

	idx = get_sprite_idx(cub, (int)x, (int)y);
	if (cub->sprites[idx].hit == 0)
		return ;
	cub->sprites[idx].hit = 1;
	i = -1;
	ptr = ray->sp_ray;
	while (++i < cub->win_h)
	{
		// cub->sprites[idx];
		++ptr;
	}
}
