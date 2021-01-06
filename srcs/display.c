/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2021/01/06 15:43:01 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_pixel_put(t_cub *cub, int x, int y, unsigned int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

static void	print_txtre_ray(t_cub *cub, t_ray *ray, int x, double px)
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

void		update_cubs(t_cub *cub)
{
	double	ratio;
	int		x;
	int		y;
	int		h_start;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
		if (ratio < 1)
			ratio = cub->win_h;
		else
			ratio = cub->win_h / ratio;
		h_start = (cub->win_h - ratio) / 2;
		y = 0;
		while (y < h_start)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		print_txtre_ray(cub, &(cub->rays[x]), x, ratio);
		y = ratio + h_start;
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
}

// void		update_cubs(t_cub *cub)
// {
// 	double	ratio;
// 	int		x;
// 	int		y;
// 	int		tmp;
// 	int		color;

// 	x = -1;
// 	while (++x < cub->win_w)
// 	{
// 		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
// 		if (ratio < 1)
// 			ratio = cub->win_h;
// 		else
// 			ratio = cub->win_h / ratio;
// 		tmp = (cub->win_h - ratio) / 2;
// 		if (cub->rays[x].hit_drxion == HIT_EAST)
// 			color = UCOLOR_BLUE;
// 		else if (cub->rays[x].hit_drxion == HIT_WEST)
// 			color = UCOLOR_BLACK;
// 		else if (cub->rays[x].hit_drxion == HIT_SOUTH)
// 			color = UCOLOR_GREY;
// 		else if (cub->rays[x].hit_drxion == HIT_NORTH)
// 			color = UCOLOR_RED;
// 		y = 0;
// 		while (y < tmp)
// 			ft_pixel_put(cub, x, y++, cub->sky_color);
// 		while (y < ratio + tmp)
// 			ft_pixel_put(cub, x, y++, color);
// 		while (y < cub->win_h)
// 			ft_pixel_put(cub, x, y++, cub->grnd_color);
// 		printf("HIT WALL => [ %.2f ; %.2f ]\n", cub->rays[x].hit_wall_x, cub->rays[x].hit_wall_y);
// 	}
// }
