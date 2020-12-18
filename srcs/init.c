/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:39:13 by besellem          #+#    #+#             */
/*   Updated: 2020/12/18 00:14:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_key(t_keys *keys, int key, void (*f)())
{
	keys->key = key;
	keys->f = f;
}

/*
** There are 7 keys to map
*/

static int	init_keys(t_cub *cub)
{
	int i;

	i = 0;
	if (!(cub->keys = (t_keys *)malloc(sizeof(t_keys) * (7 + 1))))
		return (1);
	add_key(&(cub->keys[i++]), KEY_LEFT, &ft_key_left);
	add_key(&(cub->keys[i++]), KEY_RIGHT, &ft_key_right);
	add_key(&(cub->keys[i++]), KEY_W, &ft_move_front);
	add_key(&(cub->keys[i++]), KEY_S, &ft_move_back);
	add_key(&(cub->keys[i++]), KEY_A, &ft_move_left);
	add_key(&(cub->keys[i++]), KEY_D, &ft_move_right);
	add_key(&(cub->keys[i++]), KEY_ESC, &ft_quit);
	add_key(&(cub->keys[i]), -1, NULL);
	return (0);
}

static int	init_img(t_cub *cub)
{
	if (!(cub->img = (t_img *)malloc(sizeof(t_img) * 1)))
		return (1);
	cub->img->ptr = NULL;
	return (0);
}

static void	init_ptrs(t_cub *cub)
{
	cub->txtr_no = NULL;
	cub->txtr_so = NULL;
	cub->txtr_ea = NULL;
	cub->txtr_we = NULL;
	cub->txtr_s = NULL;
	cub->map = NULL;
	cub->mlx = NULL;
	cub->win = NULL;
}

int			init_cub(t_cub *cub)
{
	if (init_keys(cub))
		return (1);
	if (init_img(cub))
		return (1);
	cub->win_w = -1;
	cub->win_h = -1;
	cub->sky_color = -1;
	cub->grnd_color = -1;
	init_ptrs(cub);
	cub->map_size_x = 0;
	cub->map_size_y = 0;
	cub->drxion = M_PI; // TO CHANGE
	cub->pos_x = 0.0;
	cub->pos_y = 0.0;
	cub->increment = 50.0;
	return (0);
}
