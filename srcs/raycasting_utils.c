/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/01/20 14:47:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
	
	if (ray->distance >= 0 && ray->distance < .1)
	{
		printf("distance:   [%.70f]\n", ray->distance);
		printf("cub->pos_x: [%f]\n", cub->pos_x);
		printf("cub->pos_y: [%f]\n", cub->pos_y);
		printf("x:          [%f]\n", x);
		printf("y:          [%f]\n\n", y);
	}
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_sp_x = x;
	ray->hit_sp_y = y;
	ray->sp_distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}
