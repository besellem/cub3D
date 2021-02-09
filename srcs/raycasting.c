/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/02/09 15:55:53 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Init a ray struct
** Use of memset to (re)set all variables to 0
*/

static void	init_ray(t_ray *ray, double angle)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->angle = angle;
	ray->tan_angle = tan(angle);
	ray->is_down = angle >= 0 && angle <= T_PI;
	ray->is_right = !(angle >= T_PI_2 && angle <= T_3PI_2);
	ray->distance = -1.0;
	ray->sp_scale = -1.0;
}

static void	check_horizontal(t_cub *cub, t_ray *ray)
{
	double x;
	double y;

	ray->yintcpt = (int)cub->pos_y + ray->is_down;
	ray->xintcpt = cub->pos_x + (ray->yintcpt - cub->pos_y) / ray->tan_angle;
	ray->ystep = ray->is_down ? 1 : -1;
	ray->xstep = 1 / ray->tan_angle;
	ray->xstep *= (!ray->is_right && ray->xstep > 0 ? -1 : 1);
	ray->xstep *= (ray->is_right && ray->xstep < 0 ? -1 : 1);
	x = ray->xintcpt;
	y = ray->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		if (cub->map[safe_min(y, !ray->is_down)][(int)x] == '1')
		{
			wall_intersect(cub, ray, x, y);
			return ;
		}
		else if (cub->map[(int)y][(int)x] == '2')
			sprite_intersect(cub, ray, 0., x, y);
		x += ray->xstep;
		y += ray->ystep;
	}
}

static void	check_vertical(t_cub *cub, t_ray *ray, t_ray *ray_horizontal)
{
	double x;
	double y;

	ray->xintcpt = (int)cub->pos_x + ray->is_right;
	ray->yintcpt = cub->pos_y + (ray->xintcpt - cub->pos_x) * ray->tan_angle;
	ray->xstep = ray->is_right ? 1 : -1;
	ray->ystep = ray->tan_angle;
	ray->ystep *= (!ray->is_down && ray->ystep > 0 ? -1 : 1);
	ray->ystep *= (ray->is_down && ray->ystep < 0 ? -1 : 1);
	ray->hit_vertical = 1;
	x = ray->xintcpt;
	y = ray->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		if (cub->map[(int)y][safe_min(x, !ray->is_right)] == '1')
		{
			wall_intersect(cub, ray, x, y);
			return ;
		}
		else if (cub->map[(int)y][(int)x] == '2')
			sprite_intersect(cub, ray, ray_horizontal->distance, x, y);
		x += ray->xstep;
		y += ray->ystep;
	}
}

/*
** Cast a ray, get the least distant hit (horizontal / vertical)
** and get the hit direction
*/

static void	set_hit_drxion(t_ray *ray)
{
	if (!ray->hit_vertical && !ray->is_down)
		ray->hit_drxion = HIT_NORTH;
	else if (!ray->hit_vertical && ray->is_down)
		ray->hit_drxion = HIT_SOUTH;
	else if (ray->hit_vertical && ray->is_right)
		ray->hit_drxion = HIT_WEST;
	else if (ray->hit_vertical && !ray->is_right)
		ray->hit_drxion = HIT_EAST;
}

static void	cast_ray(t_cub *cub, t_ray *ray, double angle)
{
	t_ray		hor;
	t_ray		ver;
	// t_uint32	tmp[cub->win_h];

	init_ray(&hor, angle);
	init_ray(&ver, angle);
	(&hor)->sp_ray = ray->sp_ray;
	(&ver)->sp_ray = ray->sp_ray;	// tmp;
	check_horizontal(cub, &hor);
	check_vertical(cub, &ver, &hor);
	if (hor.distance < 0 && ver.distance >= 0)
		*ray = ver;
	else if (ver.distance < 0 && hor.distance >= 0)
		*ray = hor;
	else if (hor.distance >= ver.distance)
		*ray = ver;
	else if (hor.distance < ver.distance)
		*ray = hor;
}

static void	init_sp_rays(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->win_w)
	{
		j = -1;
		while (++j < cub->win_h)
			(&cub->rays[i])->sp_ray[j] = 0U;
		++i;
	}
}

/*
** Cast all rays and update the sprites rays too.
** We keep and then set the new ray pointer (horizontal or vertical)
** with cub->rays[i].sp_ray because otherwise it's lost as we memset all rays
** each time.
*/

void		cast_all_rays(t_cub *cub)
{
	double	ray_angle;
	double	tmp_angle;
	int		i;

	init_sprites_hit(cub);
	init_sp_rays(cub);
	ray_angle = cub->drxion - (FOV / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		tmp_angle = ft_norm_angle(ray_angle);
		cast_ray(cub, &cub->rays[i], tmp_angle);
		set_hit_drxion(&cub->rays[i]);
		(&cub->rays[i])->distortion = cos(tmp_angle - cub->drxion);
		ray_angle += (FOV * cub->rays[i].distortion) / cub->win_w;
	}
	sprites_dump(cub);
}
