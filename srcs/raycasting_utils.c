/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/01/24 10:39:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}

static int		get_sprite_idx(t_cub *cub, int x, int y)
{
	int i;

	i = -1;
	while (++i < cub->sp_ocs)
	{
		if (cub->sprites[i].x == x && cub->sprites[i].y == y)
			break ;
	}
	return (-1);
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	int idx;

	idx = get_sprite_idx(cub, (int)x, (int)y);
	cub->sprites[idx].hit = 1;
	// printf("%.2f;%.2f: hit\n", x, y);
	(void)ray;
	// ray->hit_sp_x = x;
	// ray->hit_sp_y = y;
	// ray->sp_distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}
