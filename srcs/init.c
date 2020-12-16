/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:39:13 by besellem          #+#    #+#             */
/*   Updated: 2020/12/16 00:46:11 by besellem         ###   ########.fr       */
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

int			init_cub(t_cub *cub)
{
	if (init_keys(cub))
		return (1);
	cub->win_w = -1;
	cub->win_h = -1;
	cub->grnd_color = -1;
	cub->sky_color = -1;
	cub->pos_x = 0.0;
	cub->pos_y = 0.0;
	cub->increment = 10.0;
	return (0);
}

/*
** TO ADD:
**
** void	*mlx;
** void	*win;
** int	txtr_no;
** int	txtr_so;
** int	txtr_ea;
** int	txtr_we;
** int	txtr_s;
** char	**map;
*/
