/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2020/12/23 02:21:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_cub *cub, int x, int y, int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

void	move_player(t_cub *cub)
{
	double step;

	if (cub->turn != 0)
		cub->drxion = ft_norm_angle(cub->drxion + cub->turn * ft_deg2rad(4));
	if (cub->dh != 0)
	{
		step = cub->pos_x + cos(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)cub->pos_y][(int)step] == '0')
			cub->pos_x = step;
		step = cub->pos_y + sin(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)step][(int)cub->pos_x] == '0')
			cub->pos_y = step;
	}
	if (cub->dw != 0)
	{
		step = cub->pos_x + cub->dw * (sin(-cub->drxion) * cub->increment);
		if (cub->map[(int)cub->pos_y][(int)step] == '0')
			cub->pos_x = step;
		step = cub->pos_y + cub->dw * (cos(-cub->drxion) * cub->increment);
		if (cub->map[(int)step][(int)cub->pos_x] == '0')
			cub->pos_y = step;
	}
}

void	print_ray(t_cub *cub, t_ray *ray)
{
	double xstep;
	double ystep;

	xstep = ray->xintcpt;
	ystep = ray->yintcpt;
	while (xstep < ray->hit_wall_x && ystep < ray->hit_wall_y)
	{
		ft_pixel_put(cub, xstep * cub->cub_size, ystep * cub->cub_size, 0xFFFFFF);
		xstep += ray->xstep * 0.05;
		ystep += ray->ystep * 0.05;
	}
}

void	init_ray(t_ray *ray, double angle)
{
	ray->angle = angle;
	ray->is_down = 0;
	ray->is_right = 0;
	ray->xintcpt = 0.0;
	ray->yintcpt = 0.0;
	ray->xstep = 0.0;
	ray->ystep = 0.0;
	ray->distance = 0.0;
	ray->hit_wall_x = 0;
	ray->hit_wall_y = 0;
}

void	check_horizontal(t_cub *cub, t_ray *ray)
{
	double x;
	double y;

	ray->is_down = ray->angle > 0 && ray->angle < M_PI;
	ray->is_right = ray->angle < M_PI_2 || ray->angle > (1.5 * M_PI);
	ray->yintcpt = (int)cub->pos_y + ray->is_down;;
	ray->xintcpt = cub->pos_x + (ray->yintcpt - cub->pos_y) / tan(ray->angle);
	ray->ystep = ray->is_down ? 1 : -1;
	ray->xstep = 1 / tan(ray->angle);
	ray->xstep *= (!ray->is_right && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (ray->is_right && ray->xstep < 0) ? -1 : 1;
	x = ray->xintcpt;
	y = !ray->is_down ? ray->yintcpt - 1 : ray->yintcpt;
	while (x >= 0 && x < cub->win_w && y >= 0 && y < cub->win_h)
	{
		if (cub->map[(int)y][(int)x] != '0')
		{
			ray->hit_wall_x = x;
			ray->hit_wall_y = y;
			break ;
		}
		x += ray->xstep;
		y += ray->ystep;
	}
}

void	cast_ray(t_cub *cub, t_ray *ray, double angle)
{
	t_ray horizontal;
	t_ray vertical;

	init_ray(&horizontal, angle);
	init_ray(&vertical, angle);
	check_horizontal(cub, &horizontal);
	/*
	if (horizontal.distance > vertical.distance)
		*ray = vertical;
	else
	*/
		*ray = horizontal;
}

void	cast_all_rays(t_cub *cub)
{
	t_ray	rays[cub->win_w];
	double	ray_angle;
	int		i;

	ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		cast_ray(cub, &rays[i], ray_angle);
		print_ray(cub, &rays[i]);
		ray_angle += (ft_deg2rad(FOV) / cub->win_w);
	}
}

/*
** PRINT PLAYER'S DOT
*/

void	print_player(t_cub *cub)
{
	int size;
	int i;
	int j;

	size = 8;
	i = -(size / 2);
	while (++i < size / 2)
	{
		j = -(size / 2);
		while (++j < size / 2)
			ft_pixel_put(cub, cub->pos_x * cub->cub_size + i,
						cub->pos_y * cub->cub_size + j, 0x808080);
	}
}

void	update_player(t_cub *cub)
{
	// PRINT PLAYER'S VISION
	/*
	double	ray_angle;
	double	count;
	int		i;
	int		j;

	ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		count = 0.0;
		while ((count += .2) && cub->map[(int)(cub->pos_y + sin(ray_angle) * count)][(int)(cub->pos_x + cos(ray_angle) * count)] == '0')
		{
			j = -1;
			while (++j < cub->cub_size)
			{
				ft_pixel_put(cub,
						cub->pos_x * cub->cub_size + cos(ray_angle) * count * j,
						cub->pos_y * cub->cub_size + sin(ray_angle) * count * j,
						0xFFFFFF);
			}
		}
		ray_angle += ft_deg2rad(FOV) / cub->win_w;
	}
*/
	cast_all_rays(cub);
	print_player(cub);
}

void	put_cub(t_cub *cub, int x, int y, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < cub->cub_size)
	{
		j = -1;
		while (++j < cub->cub_size)
		{
			ft_pixel_put(cub, x * cub->cub_size + i, y * cub->cub_size + j,
						color);
		}
	}
}

void	update_map(t_cub *cub)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < cub->map_size_y)
	{
		j = 0;
		while (j < cub->map_size_x)
		{
			if (cub->map[i][j] == '0' || in_charset("NEWS", cub->map[i][j]) >= 0)
				put_cub(cub, j, i, 0xE0E0E0);
			else if (cub->map[i][j] == '1')
				put_cub(cub, j, i, 0x0);
			else if (cub->map[i][j] == '2')
				put_cub(cub, j, i, 0x8080ff);
			++j;
		}
		++i;
	}
}

void	fill_background(t_cub *cub)
{
	int x;
	int y;

	x = -1;
	while (++x < cub->win_w)
	{
		y = 0;
		while (y < cub->win_h / 2)
			ft_pixel_put(cub, x, y++, cub->sky_color);
		while (y < cub->win_h)
			ft_pixel_put(cub, x, y++, cub->grnd_color);
	}
}

void	update_view(t_cub *cub)
{
	// cub->img->ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/wall.xpm", &x, &y);
	cub->img->ptr = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	cub->img->addr = mlx_get_data_addr(cub->img->ptr,
										&(cub->img->bits_per_pixel),
										&(cub->img->size_line),
										&(cub->img->endian));
	move_player(cub);
	fill_background(cub);
	update_map(cub);
	update_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->ptr, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img->ptr);
	cub->img->ptr = NULL;
	printf("[ %f ; %f ] [ %d° ]\n",
				cub->pos_x,
				cub->pos_y,
				(int)ft_rad2deg(cub->drxion));
}
