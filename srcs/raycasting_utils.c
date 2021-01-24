/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/01/24 15:53:28 by besellem         ###   ########.fr       */
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
	int idx;

	idx = get_sprite_idx(cub, (int)x, (int)y);
	// ft_printf("sprites ocs: %d\n", cub->sp_ocs);
	// ft_printf("idx: %d, x: %d, y: %d\n", idx, (int)x, (int)y);
	// ft_printf("x: %d, y: %d\n\n", cub->sprites[idx].x, cub->sprites[idx].y);
	cub->sprites[idx].hit = 1;
	cub->sprites[idx].hit_x = x;
	cub->sprites[idx].hit_y = y;
	(void)ray;
	// ray->sp_distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}
