/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/02/17 14:57:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->distance = ft_pythagore(cub->pos_x, cub->pos_y, x, y);
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
	idx = (cub->win_h - scale) / 2;
	if (cub->win_h < scale)
	{
		idx = -1;
		start = (tx.y * (1 - cub->win_h / scale)) / 2;
		end -= start;
	}
	while (start < end && ++idx < cub->win_h)
	{
		if (ray->sp_ray[idx] == 0U)
		{
			color = *(uint32_t *)(tx.addr + (int)start * tx.size_line + \
					col_num * (tx.bpp / 8));
			if (color != 0U)
				ray->sp_ray[idx] = color;
		}
		start += tx.y / scale;
	}
}

void		set_sprite_struct(t_cub *cub, t_sprite *sprite)
{
	const double opp = cub->pos_y - (sprite->y + 0.5);
	const double adj = cub->pos_x - (sprite->x + 0.5);

	sprite->hit = 1;
	sprite->centre_angle = atan(opp / adj);
	sprite->distance = ft_pythagore(cub->pos_x, cub->pos_y,
								sprite->x + 0.5, sprite->y + 0.5);
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double horz_dist, double x, double y)
{
	t_sprite	*sprite;
	double		x_col;
	const int	idx = get_sprite_idx(cub, x, y);

	sprite = &cub->sprites[idx];
	if (sprite->hit == 0)
	{
		set_sprite_struct(cub, sprite);
	}

	
	// if (ray->hit_vertical)
	// {
	// 	printf("Vertical: angle[%.3f] dist[%.3f]\n\n", ray->angle, sprite->distance);
	// }
	// else
	// {
	// 	printf("Horizontal: angle[%.3f] dist[%.3f]\n\n", ray->angle, sprite->distance);
	// }


	if (ray->hit_vertical == 1)
	{
		if (horz_dist > 0. && sprite->distance > horz_dist)
		{
			sprite->hit = 0;
			sprite->distance = 0.;
			return ;
		}
	}

	x_col = fmod(sprite->distance * tan(ray->angle - sprite->centre_angle) \
				* cub->txtrs[4].x + cub->txtrs[4].x / 2, cub->txtrs[4].x);
	// x_col = sprite->distance * tan(ray->angle - sprite->centre_angle) \
	// 			* cub->txtrs[4].x + cub->txtrs[4].x / 2;
	fill_sprite_ptr(cub, ray, cub->win_h / sprite->distance, x_col);
}