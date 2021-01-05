/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2021/01/05 15:22:08 by besellem         ###   ########.fr       */
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

// static
void	print_texture_ray(t_cub *cub, t_img *tx, int idx, double size)
{
	char	*px;
	int		i;
	int		j;

	i = -1;
	while (++i < tx->y / 2)
	{
		j = -1;
		while (++j < tx->x)
		{
			px = tx->addr + (i * tx->size_line + j * (tx->bits_per_pixel / 8));
			ft_pixel_put(cub, j, i, *(unsigned int *)px);
		}
	}
	(void)size;
	(void)idx;
	/*
	i = -1;
	while (++i < size)
	{
		px = tx->addr + (idx * tx->size_line + i * (tx->bits_per_pixel / 8));
		ft_pixel_put(cub, idx, ((cub->win_h - size) / 2) + i, *(unsigned int *)px);
	}
	*/
}

/*
** tx:	image
*/

void	print_texture_ray_test(t_cub *cub, t_img *tx, t_ray *ray, int idx, int px)
{
	char	*ptr;
	int		ratio;
	int		i;
	int		j;

	(void)ray;
	ratio = px / tx->y;
	i = -1;
	while (++i < tx->y)
	{
		j = -1;
		while (++j < ratio)
		{
			ptr = tx->addr + (idx * tx->size_line + i * (tx->bits_per_pixel / 8));
			ft_pixel_put(cub, idx, px + i + j, *(unsigned int *)ptr);
		}
	}
}

// void		calc_txtr(t_cub *cub, t_ray *ray)
// {
	
// }

// void		update_cubs(t_cub *cub)
// {
// 	double	ratio;
// 	int		x;
// 	int		tmp;

// 	x = -1;
// 	while (++x < cub->win_w)
// 	{
// 		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
// 		if (ratio < 1)
// 			ratio = cub->win_h;
// 		else
// 			ratio = cub->win_h / ratio;
// 		tmp = (cub->win_h - ratio) / 2;

// 		if (cub->rays[x].hit_drxion == HIT_EAST)		// NORTH (UP) TEXTURE
// 			print_texture_ray_test(cub, &(cub->txtrs[0]), &(cub->rays[x]), x, (int)ratio);
// 		else if (cub->rays[x].hit_drxion == HIT_EAST)	// SOUTH (DOWN) TEXTURE
// 			print_texture_ray_test(cub, &(cub->txtrs[1]), &(cub->rays[x]), x, (int)ratio);
// 		else if (cub->rays[x].hit_drxion == HIT_EAST)	// EAST (RIGHT) TEXTURE
// 			print_texture_ray_test(cub, &(cub->txtrs[2]), &(cub->rays[x]), x, (int)ratio);
// 		else if (cub->rays[x].hit_drxion == HIT_EAST)	// WEST (LEFT) TEXTURE
// 			print_texture_ray_test(cub, &(cub->txtrs[3]), &(cub->rays[x]), x, (int)ratio);
	
// 		print_texture_ray_test(
// 			cub,
// 			&(cub->txtrs[cub->rays[x].hit_drxion]),
// 			&(cub->rays[x]),
// 			x,
// 			(int)ratio);
// 		}
// }

void		update_cubs(t_cub *cub)
{
	double	ratio;
	int		x;
	int		y;
	int		tmp;
	int		color;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cos(cub->rays[x].angle - cub->drxion);
		if (ratio < 1)
			ratio = cub->win_h;
		else
			ratio = cub->win_h / ratio;
		tmp = (cub->win_h - ratio) / 2;
		if (cub->rays[x].hit_drxion == HIT_EAST)
			color = UCOLOR_BLUE;
		else if (cub->rays[x].hit_drxion == HIT_WEST)
			color = UCOLOR_BLACK;
		else if (cub->rays[x].hit_drxion == HIT_SOUTH)
			color = UCOLOR_GREY;
		else if (cub->rays[x].hit_drxion == HIT_NORTH)
			color = UCOLOR_RED;
		y = 0;
		while (y < tmp)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		while (y < ratio + tmp)
			ft_pixel_put(cub, x, y++, color);
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
		printf("HIT WALL => [ %.2f ; %.2f ]\n", cub->rays[x].hit_wall_x, cub->rays[x].hit_wall_y);
	}
}
