/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem@student.42.fr <besellem>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:18:26 by besellem          #+#    #+#             */
/*   Updated: 2021/01/17 10:35:26 by besellem@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		ft_quit(cub);
	else if (key == KEY_W && cub->keys->key_s == 0 && (cub->dh = 1))
		cub->keys->key_w = 1;
	else if (key == KEY_S && cub->keys->key_w == 0 && (cub->dh = -1))
		cub->keys->key_s = 1;
	else if (key == KEY_D && cub->keys->key_a == 0 && (cub->dw = 1))
		cub->keys->key_d = 1;
	else if (key == KEY_A && cub->keys->key_d == 0 && (cub->dw = -1))
		cub->keys->key_a = 1;
	else if (key == KEY_LEFT && cub->keys->key_right == 0 && (cub->turn = -1))
		cub->keys->key_left = 1;
	else if (key == KEY_RIGHT && cub->keys->key_left == 0 && (cub->turn = 1))
		cub->keys->key_right = 1;
	else
		return (1);
	ft_printf("key pressed: [%d]\n", key);
	return (0);
}

int	handle_key_release(int key, t_cub *cub)
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
