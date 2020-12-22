/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2020/12/22 04:07:53 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cub->drxion += ft_deg2rad(4);
}

void	ft_key_right(t_cub *cub)
{
	cub->drxion -= ft_deg2rad(4);
}

void	ft_move_front(t_cub *cub)
{
	int x;
	int y;

	x = (int)(cub->pos_x + cos(cub->drxion) * cub->increment);
	y = (int)(cub->pos_y + sin(cub->drxion) * cub->increment);
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

	x = (int)(cub->pos_x - cos(cub->drxion) * cub->increment);
	y = (int)(cub->pos_y - sin(cub->drxion) * cub->increment);
	if (cub->map[y][x] == '0')
	{
		cub->pos_x -= cos(cub->drxion) * cub->increment;
		cub->pos_y -= sin(cub->drxion) * cub->increment;
	}
}

void	ft_move_left(t_cub *cub)
{
	double x;
	double y;

	x = cub->pos_x - sin(-cub->drxion) * cub->increment;
	y = cub->pos_y - cos(-cub->drxion) * cub->increment;
	if (cub->map[(int)cub->pos_y][(int)x] == '0')
		cub->pos_x = x;
	if (cub->map[(int)y][(int)cub->pos_x] == '0')
		cub->pos_y = y;
}

void	ft_move_right(t_cub *cub)
{
	double x;
	double y;

	x = cub->pos_x + sin(-cub->drxion) * cub->increment;
	y = cub->pos_y + cos(-cub->drxion) * cub->increment;
	if (cub->map[(int)cub->pos_y][(int)x] == '0')
		cub->pos_x = x;
	if (cub->map[(int)y][(int)cub->pos_x] == '0')
		cub->pos_y = y;
}

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

	if (cub->turn == -1)
		ft_key_right(cub);
	else if (cub->turn == 1)
		ft_key_left(cub);
	if (cub->dh != 0)
	{
		step = cub->pos_x + cos(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)cub->pos_y][(int)step] == '0')
			cub->pos_x = step;
		step = cub->pos_y + sin(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)step][(int)cub->pos_x] == '0')
			cub->pos_y = step;
	}
	if (cub->dw == 1)
		ft_move_right(cub);
	else if (cub->dw == -1)
		ft_move_left(cub);
}

void	update_player(t_cub *cub)
{
	int size = 8;
	int count;
	int i;
	int j;
	
	// PRINT PLAYER'S VISION
	double ray_angle = cub->drxion - (ft_deg2rad(FOV) / 2);
	i = -1;
	while (++i < cub->win_w)
	{
		count = 0;
		while (++count && cub->map[(int)(cub->pos_y + sin(ray_angle) * count)][(int)(cub->pos_x + cos(ray_angle) * count)] == '0')
		{
			j = -1;
			while (++j < cub->cub_size)
			{
				ft_pixel_put(cub,
						cub->pos_x * cub->cub_size + cos(ray_angle) * count * j,
						cub->pos_y * cub->cub_size + sin(ray_angle) * count * j,
						0xFF0000);
			}
		}
		ray_angle += ft_deg2rad(FOV) / cub->win_w;
	}

	// PRINT PLAYER'S DOT
	i = -(size / 2);
	while (++i < size / 2)
	{
		j = -(size / 2);
		while (++j < size / 2)
			ft_pixel_put(cub,
						(cub->pos_x * cub->cub_size) + i,
						(cub->pos_y * cub->cub_size) + j,
						0x808080);
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
	ft_printf("[ %f ; %f ] [ %d° ]\n",
				cub->pos_x,
				cub->pos_y,
				abs((int)ft_rad2deg(cub->drxion) % 360));
}

int		handle_key_press(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		ft_quit(cub);
	else if (key == KEY_W && (cub->dh = 1))
		cub->keys->key_w = 1;
	else if (key == KEY_S && (cub->dh = -1))
		cub->keys->key_s = 1;
	else if (key == KEY_D && (cub->dw = 1))
		cub->keys->key_d = 1;
	else if (key == KEY_A && (cub->dw = -1))
		cub->keys->key_a = 1;
	else if (key == KEY_LEFT && (cub->turn = -1))
		cub->keys->key_left = 1;
	else if (key == KEY_RIGHT && (cub->turn = 1))
		cub->keys->key_right = 1;
	else
		return (1);
	ft_printf("key pressed: [%d]\n", key);
	return (0);
}

int		handle_key_release(int key, t_cub *cub)
{
	if (key == KEY_W && !(cub->keys->key_w = 0) && cub->keys->key_s == 0)
		cub->dh = 0;
	else if (key == KEY_S && !(cub->keys->key_s = 0) && cub->keys->key_w == 0)
		cub->dh = 0;
	else if (key == KEY_D && !(cub->keys->key_d = 0) && cub->keys->key_a == 0)
		cub->dw = 0;
	else if (key == KEY_A && !(cub->keys->key_a = 0) && cub->keys->key_d == 0)
		cub->dw = 0;
	else if (key == KEY_LEFT && !(cub->keys->key_left = 0) &&
			cub->keys->key_right == 0)
		cub->turn = 0;
	else if (key == KEY_RIGHT && !(cub->keys->key_right = 0) &&
			cub->keys->key_left == 0)
		cub->turn = 0;
	else
		return (1);
	ft_printf("key released: [%d]\n", key);
	return (0);
}
