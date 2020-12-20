/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2020/12/20 22:33:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_quit(t_cub *cub)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	mlx_destroy_window(cub->mlx, cub->win);
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

double	ft_deg2rad(int deg)
{
	return (deg * (M_PI / 180));
}

double	ft_rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}

void	ft_key_left(t_cub *cub)
{
	double new;

	new = ft_deg2rad(6);
	if (cub->drxion + new >= (M_PI * 2))
		cub->drxion = (cub->drxion - (M_PI * 2)) + new;
	else
		cub->drxion += new;
	if (ft_rad2deg(cub->drxion) == 360)
		cub->drxion = 0;
}

void	ft_key_right(t_cub *cub)
{
	double new;

	new = ft_deg2rad(6);
	if (cub->drxion - new < 0)
		cub->drxion = (cub->drxion + (M_PI * 2)) - new;
	else
		cub->drxion -= new;
	if (ft_rad2deg(cub->drxion) == 360)
		cub->drxion = 0;
}

void	ft_move_front(t_cub *cub)
{
	int x;
	int y;

	x = (int)(cub->pos_x + cos(cub->drxion) * cub->increment) / cub->cub_size;
	y = (int)(cub->pos_y + sin(cub->drxion) * cub->increment) / cub->cub_size;
	if (cub->map[y][x] == '0')
	{
		cub->pos_x += cos(cub->drxion) * cub->increment;
		cub->pos_y += sin(cub->drxion) * cub->increment;
	}
}

void	ft_move_back(t_cub *cub)
{
	int x;
	int y;

	x = (int)(cub->pos_x - cos(cub->drxion) * cub->increment) / cub->cub_size;
	y = (int)(cub->pos_y - sin(cub->drxion) * cub->increment) / cub->cub_size;
	if (cub->map[y][x] == '0')
	{
		cub->pos_x -= cos(cub->drxion) * cub->increment;
		cub->pos_y -= sin(cub->drxion) * cub->increment;
	}
}

void	ft_move_left(t_cub *cub)
{
	int x;
	int y;

	x = (int)(cub->pos_x - sin(-cub->drxion) * cub->increment) / cub->cub_size;
	y = (int)(cub->pos_y - cos(-cub->drxion) * cub->increment) / cub->cub_size;
	if (cub->map[y][x] == '0')
	{
		cub->pos_x -= sin(-cub->drxion) * cub->increment;
		cub->pos_y -= cos(-cub->drxion) * cub->increment;
	}
}

void	ft_move_right(t_cub *cub)
{
	int x;
	int y;

	x = (int)(cub->pos_x + sin(-cub->drxion) * cub->increment) / cub->cub_size;
	y = (int)(cub->pos_y + cos(-cub->drxion) * cub->increment) / cub->cub_size;
	if (cub->map[y][x] == '0')
	{
		cub->pos_x += sin(-cub->drxion) * cub->increment;
		cub->pos_y += cos(-cub->drxion) * cub->increment;
	}
}

void	ft_pixel_put(t_cub *cub, int x, int y, int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

void	update_player(t_cub *cub)
{
	int size = 8;
	int count;
	int i;
	int j;
	int x;
	int y;

	x = (int)cub->pos_x;
	y = (int)cub->pos_y;
	i = -(size / 2);
	while (++i < size / 2)
	{
		j = -(size / 2);
		while (++j < size / 2)
			ft_pixel_put(cub, x + i, y + j, 0x808080);
	}
	double ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		count = size / 2;
		while (++count < size * 2.5)
			ft_pixel_put(cub, x + cos(ray_angle) * count, y + sin(ray_angle) * count, 0xFF0000);
		ray_angle += ft_deg2rad(FOV) / cub->win_w;
	}
}

void	put_cub(t_cub *cub, int size, int x, int y, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			ft_pixel_put(cub, x + i, y + j, color);
	}
}

void	update_map(t_cub *cub)
{
	int		size;
	size_t	i;
	size_t	j;

	size = cub->cub_size;
	i = 0;
	while (i < cub->map_size_y)
	{
		j = 0;
		while (j < cub->map_size_x)
		{
			if (cub->map[i][j] == '0' || in_charset("NEWS", cub->map[i][j]) >= 0)
				put_cub(cub, size, j * size, i * size, 0xD2D2D2);
			else if (cub->map[i][j] == '1')
				put_cub(cub, size, j * size, i * size, 0x0);
			else if (cub->map[i][j] == '2')
				put_cub(cub, size, j * size, i * size, 0x8080ff);
			++j;
		}
		++i;
	}
}

void	change_view(t_cub *cub)
{
	int x;
	int y;

	y = -1;
	while (++y < cub->win_h)
	{
		x = -1;
		while (++x < cub->win_w)
			ft_pixel_put(cub, x, y, 0xFFFFFF);
	}
	update_map(cub);
	update_player(cub);
}

void	update_view(t_cub *cub)
{
	int x;
	int y;

	x = (int)cub->pos_x;
	y = (int)cub->pos_y;
	// cub->img->ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/wall.xpm", &x, &y);
	cub->img->ptr = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	cub->img->addr = mlx_get_data_addr(cub->img->ptr,
										&(cub->img->bits_per_pixel),
										&(cub->img->size_line),
										&(cub->img->endian));
	change_view(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->ptr, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img->ptr);
	cub->img->ptr = NULL;
}

int		handle_key_event(int key, t_cub *cub)
{
	int i;

	i = -1;
	while (cub->keys[++i].f != NULL)
	{
		if (cub->keys[i].key == key)
		{
			ft_printf("key: [%d] f: [%p]\n", cub->keys[i].key, cub->keys[i].f);
			cub->keys[i].f(cub);
			ft_printf("[ %f ; %f ] [ %f ]\n", cub->pos_x, cub->pos_y, ft_rad2deg(cub->drxion));
			update_view(cub);
			break ;
		}
	}
	return (0);
}
