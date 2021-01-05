/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/01/05 10:30:27 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray, double angle)
{
	ray->angle = angle;
	ray->is_down = angle > 0 && angle < M_PI;
	ray->is_right = !(angle > M_PI_2 && angle < (1.5 * M_PI));
	ray->hit_vertical = 0;
	ray->hit_horizontal = 0;
	ray->xintcpt = 0.0;
	ray->yintcpt = 0.0;
	ray->xstep = 0.0;
	ray->ystep = 0.0;
	ray->distance = -1.0;
	ray->hit_wall_x = 0;
	ray->hit_wall_y = 0;
}

static void	check_horizontal(t_cub *cub, t_ray *ray)
{
	double x;
	double y;

	ray->yintcpt = (int)cub->pos_y + ray->is_down;
	ray->xintcpt = cub->pos_x + (ray->yintcpt - cub->pos_y) / tan(ray->angle);
	ray->ystep = ray->is_down ? 1 : -1;
	ray->xstep = 1 / tan(ray->angle);
	ray->xstep *= (!ray->is_right && ray->xstep > 0 ? -1 : 1);
	ray->xstep *= (ray->is_right && ray->xstep < 0 ? -1 : 1);
	x = ray->xintcpt;
	y = ray->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		if (cub->map[(int)(y - !ray->is_down)][(int)x] != '0')
		{
			ray->hit_wall_x = x;
			ray->hit_wall_y = y;
			ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
			break ;
		}
		x += ray->xstep;
		y += ray->ystep;
	}
}

static void	check_vertical(t_cub *cub, t_ray *ray)
{
	double x;
	double y;

	ray->xintcpt = (int)cub->pos_x + ray->is_right;
	ray->yintcpt = cub->pos_y + (ray->xintcpt - cub->pos_x) * tan(ray->angle);
	ray->xstep = ray->is_right ? 1 : -1;
	ray->ystep = tan(ray->angle);
	ray->ystep *= (!ray->is_down && ray->ystep > 0 ? -1 : 1);
	ray->ystep *= (ray->is_down && ray->ystep < 0 ? -1 : 1);
	x = ray->xintcpt;
	y = ray->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		if (cub->map[(int)y][(int)(x - !ray->is_right)] != '0')
		{
			ray->hit_wall_x = x;
			ray->hit_wall_y = y;
			ray->distance = get_dist(cub->pos_x, cub->pos_y, x, y);
			ray->hit_vertical = 1;
			break ;
		}
		x += ray->xstep;
		y += ray->ystep;
	}
}

/*
** CAST RAY, GET THE LESS DISTANT HIT (HORIZ OR VERTIC) AND GET THE HIT DRXION
*/

static void	cast_ray(t_cub *cub, t_ray *ray, double angle)
{
	t_ray hor;
	t_ray ver;

	init_ray(&hor, angle);
	init_ray(&ver, angle);
	check_horizontal(cub, &hor);
	check_vertical(cub, &ver);
	if (hor.distance < 0 && ver.distance >= 0)
		*ray = ver;
	else if (ver.distance < 0 && hor.distance >= 0)
		*ray = hor;
	else if (hor.distance > ver.distance)
		*ray = ver;
	else if (hor.distance < ver.distance)
		*ray = hor;
	if (!ray->hit_vertical && !ray->is_down)
		ray->hit_drxion = HIT_NORTH;
	else if (!ray->hit_vertical && ray->is_down)
		ray->hit_drxion = HIT_SOUTH;
	else if (ray->hit_vertical && ray->is_right)
		ray->hit_drxion = HIT_EAST;
	else if (ray->hit_vertical && !ray->is_right)
		ray->hit_drxion = HIT_WEST;
}

void		cast_all_rays(t_cub *cub)
{
	double	ray_angle;
	double	tmp_angle;
	int		i;

	ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		tmp_angle = ft_norm_angle(ray_angle);
		init_ray(&(cub->rays[i]), tmp_angle);
		cast_ray(cub, &(cub->rays[i]), tmp_angle);
		ray_angle += ft_deg2rad(FOV) / cub->win_w;
	}
}
