/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:42 by besellem          #+#    #+#             */
/*   Updated: 2021/02/28 15:34:10 by besellem         ###   ########.fr       */
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

// void		check_sp_vert(t_cub *cub, t_sprite_raycasting *sp_casting, int idx)
// {
// 	double	x;
// 	double	y;
// 	int		i;

// 	x = sp_casting->vert->xintcpt;
// 	y = sp_casting->vert->yintcpt;
// 	i = 0;
// 	while (i < idx)
// 	{
// 		x += sp_casting->vert->xstep;
// 		y += sp_casting->vert->ystep;
// 		++i;
// 	}
// 	if (cub->map[safe_min(y, !sp_casting->vert->is_down)][(int)x] != '1')
// 	{
// 		sprite_intersect(cub, sp_casting->vert, 0., x, y);
// 	}
// }

void		check_sp_horz(t_cub *cub, t_sprite_raycasting *sp_casting, int idx)
{
	double	horz_x;
	double	horz_y;
	int		i;

	horz_x = sp_casting->horz->xintcpt;
	horz_y = sp_casting->horz->yintcpt;
	i = 0;
	while (i <= idx && horz_x >= 0 && horz_x < cub->map_size_x &&
			horz_y >= 0 && horz_y < cub->map_size_y)
	{
		horz_x += sp_casting->horz->xstep;
		horz_y += sp_casting->horz->ystep;
		++i;
	}

	// horz_x = horz_x + !sp_casting->horz->is_down;
	horz_y = horz_y - sp_casting->horz->is_down;
	// printf("angle => %f\n", sp_casting->horz->angle);
	if (sp_casting->horz->angle >= T_PI_2 - .1 && sp_casting->horz->angle <= T_PI_2 + .1)
	{
		printf("([  vx  ] [  hx  ] ; [  vy  ] [  hy  ])\n");
		printf("(["B_GREEN"%6.20f"CLR_COLOR"] ["B_GREEN"%6.20f"CLR_COLOR"] ; ", sp_casting->x, horz_x);
		printf("["B_GREEN"%6.20f"CLR_COLOR"] ["B_GREEN"%6.20f"CLR_COLOR"])\n\n", sp_casting->y, horz_y);
		if ((int)sp_casting->x == 10 && (int)sp_casting->y == 10)
			printf(B_RED"VERT FOUND !"CLR_COLOR"\n");
		else if ((int)horz_x == 10 && (int)horz_y == 10)
			printf(B_RED"HORZ FOUND !"CLR_COLOR"\n");
		printf("i[%d] ocs[%d] == [%d]\n", i, sp_casting->horz_ocs, i == sp_casting->horz_ocs);
	}
	if (is_sprite(cub->map[(int)sp_casting->y][(int)sp_casting->x]))
	{
		sprite_intersect(cub, sp_casting->horz, sp_casting->x, sp_casting->y);
	}
	else if (is_sprite(cub->map[(int)horz_y][(int)horz_x]))
	{
		sprite_intersect(cub, sp_casting->vert, horz_x, horz_y);
	}
}

static void	check_horizontal(t_cub *cub, t_sprite_raycasting *sp_casting)
{
	double x;
	double y;

	x = sp_casting->horz->xintcpt;
	y = sp_casting->horz->yintcpt;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		// if (is_sprite(cub->map[(int)y][(int)x]))
		// {
		// 	sprite_intersect(cub, sp_casting->horz, x, y);
		// }
		if (cub->map[safe_min(y, !sp_casting->horz->is_down)][(int)x] == '1')
		{
			wall_intersect(cub, sp_casting->horz, x, y);
			return ;
		}
		x += sp_casting->horz->xstep;
		y += sp_casting->horz->ystep;
		sp_casting->horz_ocs++;
	}
}

static void	check_vertical(t_cub *cub, t_sprite_raycasting *sp_casting)
{
	double	x;
	double	y;
	int		idx;

	x = sp_casting->vert->xintcpt;
	y = sp_casting->vert->yintcpt;
	idx = 0;
	while (x >= 0 && x < cub->map_size_x && y >= 0 && y < cub->map_size_y)
	{
		// if (is_sprite(cub->map[(int)y][(int)x]))
		// {
		// 	sprite_intersect(cub, sp_casting->vert, x, y);
		// }
		check_sp_horz(cub, sp_casting, idx);
		if (cub->map[(int)y][safe_min(x, !sp_casting->vert->is_right)] == '1')
		{
			wall_intersect(cub, sp_casting->vert, x, y);
			return ;
		}
		x += sp_casting->vert->xstep;
		y += sp_casting->vert->ystep;
		sp_casting->x = x;
		sp_casting->y = y;
		++idx;
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
	t_sprite_raycasting	sp_casting;
	t_ray				hor;
	t_ray				ver;

	ft_memset(&sp_casting, 0, sizeof(t_sprite_raycasting));
	init_ray(cub, &hor, angle, 0);
	init_ray(cub, &ver, angle, 1);
	(&hor)->sp_ray = ray->sp_ray;
	(&ver)->sp_ray = ray->sp_ray;
	sp_casting.horz = &hor;
	sp_casting.vert = &ver;
	if (sp_casting.horz->angle >= T_PI_2 - .1 && sp_casting.horz->angle <= T_PI_2 + .1)
		printf("################\n");
	check_horizontal(cub, &sp_casting);
	check_vertical(cub, &sp_casting);
	// printf("\n");
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
