/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/02/11 16:02:51 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}

int		get_sprite_idx(t_cub *cub, int x, int y)
{
	int i;

	i = 0;
	while (i < cub->sprites_ocs - 1)
	{
		if (cub->sprites[i].x == x && cub->sprites[i].y == y)
			break ;
		++i;
	}
	return (i);
}

void	fill_sprite_ptr(t_cub *cub, t_ray *ray, double scale, int col_num)
{
	const t_img	tx = cub->txtrs[4];
	double		start;
	double		end;
	int			idx;
	t_uint32	color;

	start = 0.0;
	end = tx.y;
	idx = (cub->win_h - scale) / 2 - 0.1;
	if (cub->win_h < scale)
	{
		idx = 0;
		start = (tx.y * (1 - cub->win_h / scale)) / 2;
		end -= start;
	}
	while (start < end && idx < cub->win_h)
	{
		if (ray->sp_ray[idx] == 0U) // opti to avoid address calc below
		{
			color = *(t_uint32 *)(tx.addr + (int)start * tx.size_line + col_num * (tx.bits_per_pixel / 8));
			if (color != 0U)
			{
				ray->sp_ray[idx] = color;
				ray->hit_sprite = 1;
			}
		}
		start += tx.y / scale;
		++idx;
	}
}

void	sprite_intersect(t_cub *cub, t_ray *ray, double horz_dist, double x, double y)
{
	const int idx = get_sprite_idx(cub, x, y);

	if (cub->sprites[idx].hit == 0)
	{
		ray->hit_sprite = 1;
		cub->sprites[idx].hit = 1;
		cub->sprites[idx].distance = get_dist(cub->pos_x,
										cub->pos_y,
										cub->sprites[idx].x + 0.5,
										cub->sprites[idx].y + 0.5);
		// cub->sprites[idx].half_angle = cub->sprites[idx].distance * 
	}
	if (ray->hit_vertical == 1)
	{
		if (horz_dist > 0. && cub->sprites[idx].distance > horz_dist)
		{
			ray->hit_sprite = 0;
			cub->sprites[idx].hit = 0;
			cub->sprites[idx].distance = 0.;
		}
	}
	ray->sp_scale = cub->win_h / cub->sprites[idx].distance;
	// printf(B_RED"ray->sp_scale[%.2f] cub->sprites[idx].distance[%.2f]\n"CLR_COLOR, ray->sp_scale, cub->sprites[idx].distance);
	
	// ray->sp_scale = cub->sprites[idx].distance;
	// if (ray->sp_scale >= 0 && ray->sp_scale < 0.0001)
	// 		ray->sp_scale = 0.0001;
	// ray->sp_scale = cub->win_h / ray->sp_scale;
	
	// FOV * cub->rays[i].distortion) / cub->win_w
	double dir = cub->drxion - ray->angle;
	double test_calc = cub->sprites[idx].distance * atan(dir) * cub->txtrs[4].x;
	
	printf("x[%.2f] y[%.2f] dist[%.3f] x_calc[%.3f]\n", x, y, cub->sprites[idx].distance, test_calc);
	printf("angle: [%.2f], ray->angle: [%.2f]\n\n", cub->drxion, ray->angle);
	fill_sprite_ptr(cub, ray, ray->sp_scale, test_calc);
}

//	ADD MINIMAP RAYS BACK


// void	sprite_intersect(t_cub *cub, t_ray *ray, double horz_dist, double x, double y)
// {
// 	const int idx = get_sprite_idx(cub, x, y);

// 	if (cub->sprites[idx].hit == 0)
// 	{
// 		ray->hit_sprite = 1;
// 		cub->sprites[idx].hit = 1;
// 		cub->sprites[idx].distance = get_dist(cub->pos_x,
// 										cub->pos_y,
// 										cub->sprites[idx].x + 0.5,
// 										cub->sprites[idx].y + 0.5);
// 		cub->sprites[idx].xincrement = (cub->sprites[idx].distance / cub->txtrs[4].x) / 10;
// 	}
// 	if (ray->hit_vertical == 1)
// 	{
// 		if (horz_dist > 0. && cub->sprites[idx].distance > horz_dist)
// 		{
// 			ray->hit_sprite = 0;
// 			cub->sprites[idx].hit = 0;
// 			cub->sprites[idx].distance = 0.;
// 			return ;
// 		}
// 	}
// 	ray->sp_scale = cub->win_h / cub->sprites[idx].distance;
// 	// ray->sp_scale = cub->sprites[idx].distance;
// 	// if (ray->sp_scale >= 0 && ray->sp_scale < 0.0001)
// 	// 		ray->sp_scale = 0.0001;
// 	// ray->sp_scale = cub->win_h / ray->sp_scale;
	
// 	// double test_calc = cub->sprites[idx].distance * tan(cub->drxion - ray->angle) * cub->txtrs[4].x;

// 	printf("current[%.2f] mult[%.2f]\n", cub->sprites[idx].xcurrent, cub->sprites[idx].xcurrent * cub->txtrs[4].x);
// 	fill_sprite_ptr(cub, ray, ray->sp_scale, cub->sprites[idx].xcurrent * cub->txtrs[4].x);
// 	cub->sprites[idx].xcurrent += cub->sprites[idx].xincrement;
// }
