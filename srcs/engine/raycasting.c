/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/03/04 16:08:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Init a ray struct
** Use of memset to (re)set all variables to 0
*/

static void	init_ray(t_cub *cub, t_ray *ray, double angle, int is_vertical)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->angle = angle;
	ray->tan_ngl = tan(angle);
	ray->is_down = angle >= 0 && angle <= T_PI;
	ray->is_right = !(angle >= T_PI_2 && angle <= T_3PI_2);
	ray->distance = -1.0;
	if (is_vertical)
	{
		ray->xintcpt = (int)cub->pos_x + ray->is_right;
		ray->yintcpt = cub->pos_y + (ray->xintcpt - cub->pos_x) * ray->tan_ngl;
		ray->xstep = ray->is_right ? 1 : -1;
		ray->ystep = ray->tan_ngl;
		ray->ystep *= (!ray->is_down && ray->ystep > 0 ? -1 : 1);
		ray->ystep *= (ray->is_down && ray->ystep < 0 ? -1 : 1);
		ray->hit_vertical = 1;
	}
	else
	{
		ray->yintcpt = (int)cub->pos_y + ray->is_down;
		ray->xintcpt = cub->pos_x + (ray->yintcpt - cub->pos_y) / ray->tan_ngl;
		ray->ystep = ray->is_down ? 1 : -1;
		ray->xstep = 1 / ray->tan_ngl;
		ray->xstep *= (!ray->is_right && ray->xstep > 0 ? -1 : 1);
		ray->xstep *= (ray->is_right && ray->xstep < 0 ? -1 : 1);
	}
}

/*
** Horizontal wall raycasting
*/

static void	wall_raycasting_horizontal(t_cub *cub, t_raycasting *cast)
{
	double x;
	double y;

	x = cast->horz->xintcpt;
	y = cast->horz->yintcpt;
	while (is_in_map_limits(cub, x, y))
	{
		if (cub->map[safe_min(y, !cast->horz->is_down)][(int)x] == '1')
		{
			wall_intersect(cub, cast->horz, x, y);
			return ;
		}
		x += cast->horz->xstep;
		y += cast->horz->ystep;
	}
}

/*
** Vertical wall raycasting
*/

static void	wall_raycasting_vertical(t_cub *cub, t_raycasting *cast)
{
	double x;
	double y;

	x = cast->vert->xintcpt;
	y = cast->vert->yintcpt;
	while (is_in_map_limits(cub, x, y))
	{
		if (cub->map[(int)y][safe_min(x, !cast->vert->is_right)] == '1')
		{
			wall_intersect(cub, cast->vert, x, y);
			return ;
		}
		x += cast->vert->xstep;
		y += cast->vert->ystep;
	}
}

static void	spcasting_checks(t_cub *cub, t_raycasting *cast, t_ray *valid_ray,
							t_spcasting_vars *tmp)
{
	ft_bzero(tmp, sizeof(t_spcasting_vars));
	tmp->dist_horz = ft_pyt_like(cub->pos_x, cub->pos_y,
					cast->horz_x, cast->horz_y - !cast->horz->is_down + 0.5);
	tmp->dist_vert = ft_pyt_like(cub->pos_x, cub->pos_y,
					cast->vert_x - !cast->vert->is_right + 0.5, cast->vert_y);
	if (is_in_map_limits(cub, cast->horz_x,
		cast->horz_y - !cast->horz->is_down) &&
		tmp->dist_horz < valid_ray->cmp_distance &&
		is_sprite(cub->map[(int)cast->horz_y - !cast->horz->is_down][(int)cast->horz_x]))
	{
		tmp->horz_sp = 1;
	}
	if (is_in_map_limits(cub, cast->vert_x - !cast->vert->is_right,
		cast->vert_y) && tmp->dist_vert < valid_ray->cmp_distance &&
		is_sprite(cub->map[(int)cast->vert_y][(int)cast->vert_x - !cast->vert->is_right]))
	{
		tmp->vert_sp = 1;
	}
	if (tmp->horz_sp)// && tmp->dist_horz <= tmp->dist_vert)
	{
		tmp->horz_printable = 1;
		// if (tmp->vert_sp && tmp->dist_horz >= tmp->dist_vert)
		// 	tmp->horz_printable = 0;
		printf("horz: %f\n", tmp->dist_horz);
	}
	if (tmp->vert_sp)// && tmp->dist_horz >= tmp->dist_vert)
	{
		tmp->vert_printable = 1;
		// if (tmp->horz_sp && tmp->dist_horz <= tmp->dist_vert)
		// 	tmp->vert_printable = 0;
		printf("vert: %f\n\n", tmp->dist_vert);
	}
}

static void	ft_sp_casting(t_cub *cub, t_raycasting *cast, t_ray *valid_ray)
{
	t_spcasting_vars tmp;

	while (is_in_map_limits(cub, cast->horz_x, cast->horz_y) ||
			is_in_map_limits(cub, cast->vert_x, cast->vert_y))
	{
		spcasting_checks(cub, cast, valid_ray, &tmp);
		if (tmp.horz_printable)
		{
			sprite_intersect(cub, cast->horz,
							cast->horz_x, cast->horz_y - !cast->horz->is_down);
		}
		if (tmp.vert_printable)
		{
			sprite_intersect(cub, cast->vert,
							cast->vert_x - !cast->vert->is_right, cast->vert_y);
		}
		cast->horz_x += cast->horz->xstep;
		cast->horz_y += cast->horz->ystep;
		cast->vert_x += cast->vert->xstep;
		cast->vert_y += cast->vert->ystep;
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

static void	init_sprite(t_raycasting *cast)
{
	cast->horz_x = cast->horz->xintcpt;
	cast->horz_y = cast->horz->yintcpt;
	cast->vert_x = cast->vert->xintcpt;
	cast->vert_y = cast->vert->yintcpt;
}

static void	cast_ray(t_cub *cub, t_ray *ray, double angle)
{
	t_raycasting	cast;
	t_ray			hor;
	t_ray			ver;

	ft_memset(&cast, 0, sizeof(t_raycasting));
	init_ray(cub, &hor, angle, 0);
	init_ray(cub, &ver, angle, 1);
	(&hor)->sp_ray = ray->sp_ray;
	(&ver)->sp_ray = ray->sp_ray;
	cast.horz = &hor;
	cast.vert = &ver;
	wall_raycasting_horizontal(cub, &cast);
	wall_raycasting_vertical(cub, &cast);
	if (hor.distance < 0 && ver.distance >= 0)
		*ray = ver;
	else if (ver.distance < 0 && hor.distance >= 0)
		*ray = hor;
	else if (hor.distance >= ver.distance)
		*ray = ver;
	else if (hor.distance < ver.distance)
		*ray = hor;
	init_sprite(&cast);
	ft_sp_casting(cub, &cast, ray);
}

static void	init_sprites_rays(t_cub *cub)
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
	init_sprites_rays(cub);
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
