/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2020/12/20 02:56:09 by besellem         ###   ########.fr       */
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
		cub->drxion = DRXION_E;
	else
		cub->drxion += new;
}

void	ft_key_right(t_cub *cub)
{
	double new;

	new = ft_deg2rad(6);
	if (cub->drxion - new < 0)
		cub->drxion = M_PI * 2 - new;
	else
		cub->drxion -= new;
}

void	ft_move_front(t_cub *cub)
{
	cub->pos_y += cub->increment;
}

void	ft_move_back(t_cub *cub)
{
	cub->pos_y -= cub->increment;
}

void	ft_move_left(t_cub *cub)
{
	cub->pos_x -= cub->increment;
}

void	ft_move_right(t_cub *cub)
{
	cub->pos_x += cub->increment;
}

void	ft_pixel_put(t_cub *cub, int x, int y, int color)
{
	char *px;

	px = cub->img->addr;
	px += (y * cub->img->size_line + x * (cub->img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
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
		{
			if (y % 2 == 0)
				ft_pixel_put(cub, x, y, 0xFFFFFF);
			else
				ft_pixel_put(cub, x, y, 0x7f7f7f);
		}
	}
	x = (int)cub->pos_x;
	y = (int)cub->pos_y;
	ft_pixel_put(cub, x, y, 0x0);
	ft_pixel_put(cub, x + 1, y, 0x0);
	ft_pixel_put(cub, x, y + 1, 0x0);
	ft_pixel_put(cub, x + 1, y + 1, 0x0);
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
