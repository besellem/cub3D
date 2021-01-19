/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2021/01/19 13:32:17 by besellem         ###   ########.fr       */
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
** PRINT A RAY OF TEXTURE
*/

void	print_txtre_ray(t_cub *cub, t_ray *ray, int x, double px)
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
** (?) PRINT A RAY OF SPRITE
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

void	update_cubs(t_cub *cub)
{
	double	ratio;
	int		x;
	int		y;
	int		h_start;

	x = -1;
	while (++x < cub->win_w)
	{
		ratio = cub->rays[x].distance * cub->rays[x].distortion;
		if (ratio < 1)
			ratio = cub->win_h;
		else
			ratio = cub->win_h / ratio;
		h_start = (cub->win_h - ratio) / 2;
		y = 0;
		while (y < h_start)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		print_txtre_ray(cub, &(cub->rays[x]), x, ratio);
		// print_sprite_ray(cub, &(cub->rays[x]), x, ratio);
		y = ratio + h_start;
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
}

// void	init_display(t_cub *cub, t_ray *ray, t_display *dsp)
// {
// 	dsp->ratio = cub->win_h / (ray->distance * ray->distortion);
// 	dsp->t_win_start = (cub->win_h - dsp->ratio) / 2;
// 	if (dsp->t_win_start < 0)
// 	{
// 		dsp->t_start = -dsp->t_win_start / cub->win_h;
// 		dsp->t_end = cub->win_h - dsp->t_start;
// 		dsp->t_win_start = 0;
// 		dsp->t_win_end = cub->win_h;
// 	}
// 	else
// 	{
// 		dsp->t_start = 0;
// 		dsp->t_end = cub->txtrs[ray->hit_drxion].y;
// 		dsp->t_win_end = dsp->ratio + dsp->t_win_start;
// 	}
// }

// void		tst_ray(t_cub *cub, t_ray *ray, t_display *dsp, int idx)
// {
// 	t_img	tx;
// 	char	*ptr;
// 	int		x;
// 	double	y;

// 	tx = cub->txtrs[ray->hit_drxion];
// 	y = dsp->t_start;
// 	while (y < dsp->t_end)
// 	{
// 		if (ray->hit_drxion == HIT_NORTH || ray->hit_drxion == HIT_SOUTH)
// 			x = tx.x * get_dec(ray->hit_wall_x);
// 		else if (ray->hit_drxion == HIT_EAST || ray->hit_drxion == HIT_WEST)
// 			x = tx.x * get_dec(ray->hit_wall_y);
// 		ptr = tx.addr + (int)y * tx.size_line + x * (tx.bits_per_pixel / 8);
// 		ft_pixel_put(cub, idx, dsp->t_win_start + y, *(unsigned int *)ptr);
// 		y += tx.y / (dsp->t_win_end - dsp->t_win_start);
// 	}
// }

// void		update_cubs(t_cub *cub)
// {
// 	t_display	dsp;
// 	int			x;
// 	int			y;

// 	x = -1;
// 	while (++x < cub->win_w)
// 	{
// 		init_display(cub, &(cub->rays[x]), &dsp);
// 		y = 0;
// 		while (y < dsp.t_win_start)
// 			ft_pixel_put(cub, x, y++, cub->sky_color);
// 		tst_ray(cub, &(cub->rays[x]), &dsp, x);
// 		y = dsp.t_win_end;
// 		while (y < cub->win_h)
// 			ft_pixel_put(cub, x, y++, cub->grnd_color);
// 	}
// }
