/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/02/16 11:24:49 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
}

int			get_sprite_idx(t_cub *cub, int x, int y)
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

static void	fill_sprite_ptr(t_cub *cub, t_ray *ray, double scale, int col_num)
{
	const t_img	tx = cub->txtrs[4];
	double		start;
	double		end;
	int			idx;
	uint32_t	color;

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
			color = *(uint32_t *)(tx.addr + (int)start * tx.size_line + col_num * (tx.bpp / 8));
			if (color != 0U && (ray->hit_sprite = 1))
				ray->sp_ray[idx] = color;
		}
		start += tx.y / scale;
		++idx;
	}
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double horz_dist, double x, double y)
{
	const int	idx = get_sprite_idx(cub, x, y);
	t_sprite	sp;

	sp = cub->sprites[idx];
	if (sp.hit == 0)
	{
		ray->hit_sprite = 1;
		sp.hit = 1;
		sp.distance = get_dist(cub->pos_x,
										cub->pos_y,
										sp.x + 0.5,
										sp.y + 0.5);
		
		double opp = fabs(cub->pos_y - (sp.y + 0.5));
		double adj = fabs(cub->pos_x - (sp.x + 0.5));
		double hyp = sp.distance;

		(void)opp;
		(void)adj;
		(void)hyp;

		sp.centre_angle = tan(opp / adj);
		printf(B_YELLOW"opp[%.2f] adj[%.2f] hyp[%.2f]"CLR_COLOR"\n", opp, adj, hyp);
		printf("drxion[%f] sp.centre_angle[%f]\n", ft_rad2deg(cub->drxion), ft_rad2deg(sp.centre_angle));
	}
	if (ray->hit_vertical == 1)
	{
		if (horz_dist > 0. && sp.distance > horz_dist)
		{
			ray->hit_sprite = 0;
			sp.hit = 0;
			sp.distance = 0.;
			// return ; // (?)
		}
	}
	ray->sp_scale = cub->win_h / sp.distance;
	// printf(B_RED"ray->sp_scale[%.2f] sp.distance[%.2f]\n"CLR_COLOR, ray->sp_scale, sp.distance);
	
	// ray->sp_scale = sp.distance;
	// if (ray->sp_scale >= 0 && ray->sp_scale < 0.0001)
	// 		ray->sp_scale = 0.0001;
	// ray->sp_scale = cub->win_h / ray->sp_scale;
	

	// double x_calc = sp.distance * atan(cub->drxion - ray->angle) * cub->txtrs[4].x - cub->txtrs[4].x / 2;
	double x_calc = sp.distance * cub->txtrs[4].x;

	x_calc *= tan(fabs(sp.centre_angle - ray->angle));

	printf("x_calc[%d] ", (int)x_calc);

	x_calc = x_calc + cub->txtrs[4].x / 2;

	printf("x_calc_no_dist[%d]\n", (int)x_calc);

	// printf("x[%.2f] y[%.2f] dist[%.3f] x_calc[%.3f]\n", x, y, sp.distance, x_calc);
	// printf("angle: [%.2f], ray->angle: [%.2f]\n\n", cub->drxion, ray->angle);
	fill_sprite_ptr(cub, ray, ray->sp_scale, x_calc);
}

// void		sprite_intersect(t_cub *cub, t_ray *ray, double horz_dist, double x, double y)
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
