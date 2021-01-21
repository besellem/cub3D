/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2021/01/21 09:31:03 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** PRINT A PIXEL AT THE COORDINATES INTO mlx->img
*/

void	ft_pixel_put(t_cub *cub, int x, int y, unsigned int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

/*
** /!\ PRINT SPRITE COLUMN /!\
** -- IN PROCESS --
*/

void	print_sprite_ray(t_cub *cub, t_ray *ray, int x, double px)
{
	t_img	tx;
	char	*ptr;
	int		tmp;
	double	i;
	int		j;

	tx = cub->txtrs[ray->hit_drxion];
	j = 0;
	i = 0.;
	while (i < tx.y - .01)
	{
		if (ray->hit_drxion == HIT_NORTH || ray->hit_drxion == HIT_SOUTH)
			tmp = tx.x * get_dec(ray->hit_wall_x);
		else if (ray->hit_drxion == HIT_EAST || ray->hit_drxion == HIT_WEST)
			tmp = tx.x * get_dec(ray->hit_wall_y);
		ptr = tx.addr + (int)i * tx.size_line + tmp * (tx.bits_per_pixel / 8);
		ft_pixel_put(cub, x, ((cub->win_h - px) / 2) + j, *(unsigned int *)ptr);
		i += tx.y / px;
		++j;
	}
}

/*
** PRINT A TEXTURE COLUMN DEFINED BY A RAY
*/

int		hit_x_calc(t_img tx, t_ray ray)
{
	if (ray.hit_drxion == HIT_NORTH || ray.hit_drxion == HIT_SOUTH)
		return (tx.x * get_dec(ray.hit_wall_x));
	else
		return (tx.x * get_dec(ray.hit_wall_y));
}

void	print_txtre_ray(t_cub *cub, t_ray ray, int x, double scale)
{
	t_img	tx;
	double	start;
	double	end;
	int		idx;

	tx = cub->txtrs[ray.hit_drxion];
	start = 0.0;
	end = tx.y;
	idx = (cub->win_h - scale) / 2 - 0.1;
	if (cub->win_h < scale)
	{
		idx = 0;
		start = (tx.y * (1 - cub->win_h / scale)) / 2;
		end -= start;
	}
	while (start < end && idx < cub->win_h)// - .01)
	{
		ft_pixel_put(cub, x, idx++,
			*(unsigned int *)(tx.addr + (int)start * tx.size_line + \
			hit_x_calc(tx, ray) * (tx.bits_per_pixel / 8)));
		start += tx.y / scale;
	}
}

void	update_cubs(t_cub *cub)
{
	double	scale;
	int		x;
	int		y;
	double		h_start;

	x = -1;
	while (++x < cub->win_w)
	{
		scale = cub->win_h / (cub->rays[x].distance * cub->rays[x].distortion);
		if (cub->rays[x].distance >= 0 && cub->rays[x].distance < 0.001)
			scale = 0.001; //0.01 * cub->rays[x].distortion;
		else
			scale = cub->rays[x].distance * cub->rays[x].distortion;
		scale = cub->win_h / scale;
		h_start = (cub->win_h - scale) / 2;
		y = 0;
		while (y < h_start)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		print_txtre_ray(cub, cub->rays[x], x, scale);
		// print_sprite_ray(cub, cub->rays[x], x, scale);
		y = scale + h_start;
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
}
