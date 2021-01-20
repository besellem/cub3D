/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2021/01/20 21:10:25 by besellem         ###   ########.fr       */
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
	idx = (cub->win_h - scale) / 2;
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
		start += fabs(tx.y / scale); // fabs() not necessary
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
		// if (cub->rays[x].distance >= 0 && cub->rays[x].distance < 0.01)
		// 	scale = 1; //0.01 * cub->rays[x].distortion;
		// else
		// 	scale = cub->rays[x].distance * cub->rays[x].distortion;
		// scale = cub->win_h / scale;
		h_start = (cub->win_h - scale) / 2;

		if (scale > 1000)
		{
			printf("cub->win_h:              [%d]\n", cub->win_h);
			printf("scale:                   [%f]\n", scale);
			printf("cub->win_h - scale:      [%f]\n", cub->win_h - scale);
			printf("h_start:                 [%f]\n", h_start);
			printf("cub->rays[x].angle:      [%f]\n", cub->rays[x].angle);
			printf("distance * distortion:   [%f]\n", cub->rays[x].distance * cub->rays[x].distortion);
			printf("cub->rays[x].distance:   [%.24f]\n", cub->rays[x].distance);
			printf("cub->rays[x].distortion: [%f]\n", cub->rays[x].distortion);
			printf("cub->rays[x].hit_drxion: [%d]\n", cub->rays[x].hit_drxion);
			printf("cub->rays[x].xintcpt:    [%.10f]\n", cub->rays[x].xintcpt);
			printf("cub->rays[x].yintcpt:    [%.10f]\n", cub->rays[x].yintcpt);
			printf("cub->rays[x].xstep:      [%.10f]\n", cub->rays[x].xstep);
			printf("cub->rays[x].ystep:      [%.10f]\n", cub->rays[x].ystep);
			printf("cub->rays[x].hit_wall_x: [%f]\n", cub->rays[x].hit_wall_x);
			printf("cub->rays[x].hit_wall_y: [%f]\n\n", cub->rays[x].hit_wall_y);
		}

		y = 0;
		while (y < h_start)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		print_txtre_ray(cub, cub->rays[x], x, scale);
		// print_sprite_ray(cub, cub->rays[x], x, scale);
		y = scale + h_start;
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
	// ft_error("DEBUGGER -> OK UNTIL THIS POINT", cub, __FILE__, __LINE__);
}


// // OLD
// void	print_txtre_ray(t_cub *cub, t_ray *ray, int x, double px)
// {
// 	t_img	tx;
// 	char	*ptr;
// 	int		tmp;
// 	double	i;
// 	int		j;

// 	tx = cub->txtrs[ray->hit_drxion];
// 	j = 0;
// 	i = 0.0;//(cub->win_h - px) / 2;
// 	while (i < tx.y - .01)
// 	{
// 		if (ray->hit_drxion == HIT_NORTH || ray->hit_drxion == HIT_SOUTH)
// 			tmp = tx.x * get_dec(ray->hit_wall_x);
// 		else if (ray->hit_drxion == HIT_EAST || ray->hit_drxion == HIT_WEST)
// 			tmp = tx.x * get_dec(ray->hit_wall_y);
// 		ptr = tx.addr + (int)i * tx.size_line + tmp * (tx.bits_per_pixel / 8);
// 		ft_pixel_put(cub, x, ((cub->win_h - px) / 2) + j, *(unsigned int *)ptr);
// 		i += tx.y / px;
// 		++j;
// 	}
// }

// void	update_cubs(t_cub *cub)
// {
// 	double	ratio;
// 	int		x;
// 	int		y;
// 	int		h_start;

// 	x = -1;
// 	while (++x < cub->win_w)
// 	{
// 		ratio = cub->rays[x].distance * cub->rays[x].distortion;
// 		if (ratio < 1)
// 			ratio = cub->win_h;
// 		else
// 			ratio = cub->win_h / ratio;
// 		h_start = (cub->win_h - ratio) / 2;

// 		printf("scale:                   [%f]\n", ratio);
// 		printf("distance * distortion:   [%f]\n", cub->rays[x].distance * cub->rays[x].distortion);
// 		printf("h_start:                 [%d]\n", h_start);
// 		printf("cub->rays[x].angle:      [%f]\n", cub->rays[x].angle);
// 		printf("cub->rays[x].distance:   [%.32f]\n", cub->rays[x].distance);
// 		printf("cub->rays[x].distortion: [%f]\n", cub->rays[x].distortion);
// 		printf("cub->rays[x].hit_wall_x: [%f]\n", cub->rays[x].hit_wall_x);
// 		printf("cub->rays[x].hit_wall_y: [%f]\n\n", cub->rays[x].hit_wall_y);

// 		y = 0;
// 		while (y < h_start)
// 			ft_pixel_put(cub, x, y++, cub->sky_color);
// 		print_txtre_ray(cub, &(cub->rays[x]), x, ratio);
// 		// print_sprite_ray(cub, &(cub->rays[x]), x, ratio);
// 		y = ratio + h_start;
// 		while (y < cub->win_h)
// 			ft_pixel_put(cub, x, y++, cub->grnd_color);
// 	}
// }
// // END OLD
