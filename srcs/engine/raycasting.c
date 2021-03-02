/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/03/02 16:07:49 by besellem         ###   ########.fr       */
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

// void		sp_second_idea(t_cub *cub, t_raycasting *cast, int idx)
// {
// 	double	horz_x;
// 	double	horz_y;
// 	int		i;

// 	horz_x = cast->horz->xintcpt;
// 	horz_y = cast->horz->yintcpt;
// 	i = 0;
// 	while (i < idx && horz_x >= 0 && horz_x < cub->map_size_x &&
// 			horz_y >= 0 && horz_y < cub->map_size_y)
// 	{
// 		horz_x += cast->horz->xstep;
// 		horz_y += cast->horz->ystep;
// 		++i;
// 	}
// 	if (is_sprite(cub->map[(int)cast->y][(int)cast->x]))
// 	{
// 		sprite_intersect(cub, cast->vert, cast->x, cast->y);
// 	}
// 	else if (i == idx)// && is_sprite(cub->map[(int)horz_y][(int)horz_x]))
// 	{
// 		if (cast->horz->is_down)
// 			sprite_intersect(cub, cast->horz, horz_x, horz_y + cast->horz->is_down);
// 		else
// 			sprite_intersect(cub, cast->horz, horz_x, horz_y);
// 	}
// }

static void	check_horizontal(t_cub *cub, t_raycasting *cast)
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

static void	check_vertical(t_cub *cub, t_raycasting *cast)
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

void	ft_sp_casting(t_cub *cub, t_raycasting *cast)
{
	while (is_in_map_limits(cub, cast->horz_x, cast->horz_y) ||
			is_in_map_limits(cub, cast->vert_x, cast->vert_y))
	{
		if (is_in_map_limits(cub, cast->horz_x, cast->horz_y - !cast->horz->is_down) &&
			// cast->horz_x < cast->horz->hit_wall_x &&
			// cast->horz_y < cast->horz->hit_wall_y &&
			is_sprite(cub->map[(int)cast->horz_y - !cast->horz->is_down][(int)cast->horz_x]))
		{
			sprite_intersect(cub, cast->horz, cast->horz_x, cast->horz_y - !cast->horz->is_down);
		}
		if (is_in_map_limits(cub, cast->vert_x - !cast->vert->is_right, cast->vert_y) &&
			// cast->vert_x < cast->vert->hit_wall_x &&
			// cast->vert_y < cast->vert->hit_wall_y &&
			is_sprite(cub->map[(int)cast->vert_y][(int)cast->vert_x - !cast->vert->is_right]))
		{
			sprite_intersect(cub, cast->vert, cast->vert_x - !cast->vert->is_right, cast->vert_y);
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

void		init_sprite(t_raycasting *cast, t_ray *hor, t_ray *ver)
{
	cast->vert_x = ver->xintcpt;
	cast->vert_y = ver->yintcpt;
	cast->horz_x = hor->xintcpt;
	cast->horz_y = hor->yintcpt;
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
	check_horizontal(cub, &cast);
	check_vertical(cub, &cast);

	init_sprite(&cast, &hor, &ver);
	ft_sp_casting(cub, &cast);

	if (hor.distance < 0 && ver.distance >= 0)
		*ray = ver;
	else if (ver.distance < 0 && hor.distance >= 0)
		*ray = hor;
	else if (hor.distance >= ver.distance)
		*ray = ver;
	else if (hor.distance < ver.distance)
		*ray = hor;
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
