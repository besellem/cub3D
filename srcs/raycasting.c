/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/02/02 16:02:40 by besellem         ###   ########.fr       */
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
		else if (cub->map[safe_min(y, !ray->is_down)][(int)x] == '2')
			sprite_intersect(cub, ray, x, y);
		x += ray->xstep;
		y += ray->ystep;
	}
}

static void	check_vertical(t_cub *cub, t_ray *ray)
{
	double x;
	double y;

	ray->xintcpt = (int)cub->pos_x + ray->is_right;
	ray->yintcpt = cub->pos_y + (ray->xintcpt - cub->pos_x) * ray->tan_angle;
	ray->xstep = ray->is_right ? 1 : -1;
	ray->ystep = ray->tan_angle;
	ray->ystep *= (!ray->is_down && ray->ystep > 0 ? -1 : 1);
	ray->ystep *= (ray->is_down && ray->ystep < 0 ? -1 : 1);
	x = ray->xintcpt;
	y = ray->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		if (cub->map[(int)y][safe_min(x, !ray->is_right)] == '1')
		{
			wall_intersect(cub, ray, x, y);
			ray->hit_vertical = 1;
			return ;
		}
		else if (cub->map[(int)y][safe_min(x, !ray->is_right)] == '2')
			sprite_intersect(cub, ray, x, y);
		x += ray->xstep;
		y += ray->ystep;
	}
}

/*
** Cast a ray, get the least distant hit (horizontal / vertical)
** and get the hit direction
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
	else if (hor.distance >= ver.distance)
		*ray = ver;
	else if (hor.distance < ver.distance)
		*ray = hor;
	if (!ray->hit_vertical && !ray->is_down)
		ray->hit_drxion = HIT_NORTH;
	else if (!ray->hit_vertical && ray->is_down)
		ray->hit_drxion = HIT_SOUTH;
	else if (ray->hit_vertical && ray->is_right)
		ray->hit_drxion = HIT_WEST;
	else if (ray->hit_vertical && !ray->is_right)
		ray->hit_drxion = HIT_EAST;
}

int		hit_x_sprite_calc(t_img tx, t_ray ray, double x, double y)
{
	if (ray.hit_drxion == HIT_NORTH || ray.hit_drxion == HIT_SOUTH)
		return (tx.x * get_dec(x));
	else
		return (tx.x * get_dec(y));
}

void	fill_sprite_ptr(t_cub *cub, t_ray *ray, double scale, int col_num)
{
	t_img		tx;
	double		start;
	double		end;
	int			idx;
	t_uint32	color;

	tx = cub->txtrs[4];
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
		color = *(t_uint32 *)(tx.addr + (int)start * tx.size_line + col_num * (tx.bits_per_pixel / 8));
		if (color != 0U)
		{
			ray->sp_ray[idx] = color;
			ray->hit_sprite = 1;
		}
		start += tx.y / scale;
		++idx;
	}
}

void		fill_sprite_ray(t_cub *cub, t_ray *ray)
{
	double	x;
	double	y;

	x = ray->hit_wall_x;
	y = ray->hit_wall_y;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y &&
		(int)x != (int)cub->pos_x + !ray->is_right &&
		(int)y != (int)cub->pos_y + !ray->is_down)
	{
		if ((ray->hit_vertical &&
			cub->map[(int)y][safe_min(x, !ray->is_right)] == '2') ||
			(!ray->hit_vertical &&
			cub->map[safe_min(y, !ray->is_down)][(int)x] == '2'))
		{
			
			// IDEA IN PROCESS
			if (ray->sp_scale == -1 && ray->hit_vertical)
			{
				if (get_dec(x) < 0.5)
					ray->sp_scale = get_dist(cub->pos_x, cub->pos_y, x, y - 0.5 + get_dec(x));
				else
					ray->sp_scale = get_dist(cub->pos_x, cub->pos_y, x, y - 0.5 - get_dec(x));
			}
			else if (ray->sp_scale == -1 && !ray->hit_vertical)
			{
				if (get_dec(y) < 0.5)
					ray->sp_scale = get_dist(cub->pos_x, cub->pos_y, x - 0.5 + get_dec(y), y);
				else
					ray->sp_scale = get_dist(cub->pos_x, cub->pos_y, x - 0.5 - get_dec(y), y);
			}
			// END IDEA

			if (ray->sp_scale >= 0 && ray->sp_scale < 0.0001)
				ray->sp_scale = 0.0001;
			// else
			// 	ray->sp_scale *= ray->distortion;
			ray->sp_scale = cub->win_h / ray->sp_scale;
			fill_sprite_ptr(cub, ray, ray->sp_scale, hit_x_sprite_calc(cub->txtrs[4], *ray, x, y));
		}
		x -= ray->xstep;
		y -= ray->ystep;
	}
}

void	init_sp_rays(t_cub *cub)
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
	double		ray_angle;
	double		tmp_angle;
	t_uint32	*sp_ray_ptr;
	int			i;

	init_sprites_hit(cub);
	init_sp_rays(cub);
	ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		sp_ray_ptr = (&cub->rays[i])->sp_ray;
		tmp_angle = ft_norm_angle(ray_angle);
		cast_ray(cub, &cub->rays[i], tmp_angle);
		(&cub->rays[i])->sp_ray = sp_ray_ptr;
		(&cub->rays[i])->distortion = cos(tmp_angle - cub->drxion);
		fill_sprite_ray(cub, &cub->rays[i]);
		ray_angle += (ft_deg2rad(FOV) * cub->rays[i].distortion) / cub->win_w;
	}
}
