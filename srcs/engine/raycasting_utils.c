/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/03/09 14:05:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	ray->hit_wall_x = x;
	ray->hit_wall_y = y;
	ray->cmp_distance = ft_pyt_like(cub->pos_x, cub->pos_y, x, y);
	ray->distance = sqrt(ray->cmp_distance);
}

int			get_sprite_idx(t_cub *cub, int x, int y)
{
	int i;

	i = 0;
	while (i < cub->sprites_ocs)
	{
		if (cub->sprites[i].x == x && cub->sprites[i].y == y)
			return (i);
		++i;
	}
	return (-1);
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
	idx = (int)((cub->win_h - scale) / 2) - 1;
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

static void	set_sprite_struct(t_cub *cub, t_sprite *sprite, __attribute__((unused)) double ray_angle)
{
	const double opp = cub->pos_y - sprite->y - 0.5;
	const double adj = cub->pos_x - sprite->x - 0.5;

	sprite->hit = 1;
	sprite->centre_angle = atan(opp / adj);
	sprite->distance = ft_pythagore(cub->pos_x, cub->pos_y,
						sprite->x + 0.5, sprite->y + 0.5);// * \
						// cos(cub->drxion - (ray_angle + sprite->centre_angle));
}

void		sprite_intersect(t_cub *cub, t_ray *ray, double x, double y)
{
	t_sprite	*sprite;
	int			x_col;
	const int	idx = get_sprite_idx(cub, (int)x, (int)y);

	if (idx == -1)
		return ;
	sprite = &cub->sprites[idx];
	if (sprite->hit == 0)
		set_sprite_struct(cub, sprite, ray->angle);
	x_col = sprite->distance * tan(ray->angle - sprite->centre_angle) * \
			cub->txtrs[4].x + cub->txtrs[4].x / 2;
	if (x_col >= cub->txtrs[4].x)
		x_col = cub->txtrs[4].x - 1;
	else if (x_col < 0)
		x_col = 0;
	if (x_col >= 0 && x_col <= cub->txtrs[4].x)
		fill_sprite_ptr(cub, ray, cub->win_h / sprite->distance, x_col);
}
