/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:26 by besellem          #+#    #+#             */
/*   Updated: 2021/03/11 20:18:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** REINITIALIZE EACH SPRITE'S STRUCT (EXCEPT ITS COORDINATES)
** The use of memset is useful here in case of modifications on t_sprite struct
*/

void		init_sprites_hit(t_cub *cub)
{
	int tmp_x;
	int tmp_y;
	int i;

	i = -1;
	while (++i < cub->sprites_ocs)
	{
		tmp_x = cub->sprites[i].x;
		tmp_y = cub->sprites[i].y;
		ft_memset(&cub->sprites[i], 0, sizeof(t_sprite));
		(&cub->sprites[i])->x = tmp_x;
		(&cub->sprites[i])->y = tmp_y;
	}
}

/*
** Re-init sprites rays to 0
*/

void		init_sprites_rays(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->win_w)
	{
		j = 0;
		while (j < cub->win_h)
		{
			cub->rays[i].sp_ray[j] = 0U;
			++j;
		}
		++i;
	}
}

static void	order_and_fill_sprites(t_cub *cub, t_raycasting *cast,
								t_spcasting_vars *tmp)
{
	if (tmp->order)
	{
		if (tmp->horz_printable)
			sprite_intersect(cub, cast->horz,
							cast->horz_x, cast->horz_y - !cast->horz->is_down);
		if (tmp->vert_printable)
			sprite_intersect(cub, cast->vert,
							cast->vert_x - !cast->vert->is_right, cast->vert_y);
	}
	else
	{
		if (tmp->vert_printable)
			sprite_intersect(cub, cast->vert,
							cast->vert_x - !cast->vert->is_right, cast->vert_y);
		if (tmp->horz_printable)
			sprite_intersect(cub, cast->horz,
							cast->horz_x, cast->horz_y - !cast->horz->is_down);
	}
}

static void	sprite_raycasting_z_axis(t_cub *cub, t_raycasting *cast,
							t_ray *valid_ray, t_spcasting_vars *tmp)
{
	tmp->dist_horz = ft_pyt_like(cub->pos_x, cub->pos_y, cast->horz_x,
								cast->horz_y);
	tmp->dist_vert = ft_pyt_like(cub->pos_x, cub->pos_y, cast->vert_x,
								cast->vert_y);
	if (in_map_limits(cub, cast->horz_x, cast->horz_y - !cast->horz->is_down)
		&& tmp->dist_horz < valid_ray->cmp_distance &&
		is_sprite(cub->map[(int)cast->horz_y - \
		!cast->horz->is_down][(int)cast->horz_x]))
		tmp->horz_sp = 1;
	if (in_map_limits(cub, cast->vert_x - !cast->vert->is_right, cast->vert_y)
		&& tmp->dist_vert < valid_ray->cmp_distance &&
		is_sprite(cub->map[(int)cast->vert_y][(int)cast->vert_x - \
		!cast->vert->is_right]))
		tmp->vert_sp = 1;
	if (tmp->horz_sp)
		tmp->horz_printable = 1;
	if (tmp->vert_sp)
		tmp->vert_printable = 1;
	if (tmp->horz_sp && tmp->vert_sp)
		if (tmp->dist_horz < tmp->dist_vert)
			tmp->order = 1;
}

void		sprites_raycasting(t_cub *cub, t_raycasting *cast, t_ray *valid_ray)
{
	t_spcasting_vars tmp;

	while (in_map_limits(cub, cast->horz_x, cast->horz_y) ||
			in_map_limits(cub, cast->vert_x, cast->vert_y))
	{
		ft_bzero(&tmp, sizeof(t_spcasting_vars));
		sprite_raycasting_z_axis(cub, cast, valid_ray, &tmp);
		order_and_fill_sprites(cub, cast, &tmp);
		cast->horz_x += cast->horz->xstep;
		cast->horz_y += cast->horz->ystep;
		cast->vert_x += cast->vert->xstep;
		cast->vert_y += cast->vert->ystep;
	}
}
