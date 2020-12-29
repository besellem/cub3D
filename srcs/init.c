/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:39:13 by besellem          #+#    #+#             */
/*   Updated: 2020/12/29 18:05:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_img(t_cub *cub)
{
	if (!(cub->img = (t_img *)malloc(sizeof(t_img))))
		return (1);
	cub->img->ptr = NULL;
	cub->img->addr = NULL;
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

static int	init_keys(t_cub *cub)
{
	if (!(cub->keys = (t_keys *)malloc(sizeof(t_keys))))
		return (1);
	cub->keys->key_w = 0;
	cub->keys->key_s = 0;
	cub->keys->key_a = 0;
	cub->keys->key_d = 0;
	cub->keys->key_left = 0;
	cub->keys->key_right = 0;
	return (0);
}

/*
** cub->rays is malloc in the parser as we don't know win_w & win_h yet
*/

int			init_cub(t_cub *cub)
{
	if (init_img(cub))
		return (1);
	cub->win_w = -1;
	cub->win_h = -1;
	cub->sky_color = -1;
	cub->grnd_color = -1;
	init_ptrs(cub);
	cub->map_size_x = 0;
	cub->map_size_y = 0;
	cub->drxion = 0.0;
	cub->turn = 0;
	cub->dw = 0;
	cub->dh = 0;
	cub->pos_x = 0.0;
	cub->pos_y = 0.0;
	cub->increment = 0.1;
	cub->cub_size = 8;
	if (init_keys(cub))
		return (1);
	return (0);
}
