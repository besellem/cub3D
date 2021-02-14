/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2021/02/14 15:48:23 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_start(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, NAME);
	cub->img.ptr = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr,
										&(cub->img.bits_per_pixel),
										&(cub->img.size_line),
										&(cub->img.endian));
	// To remove
	print_specs(cub);
	sprites_dump(cub);
	// end
	update_frame(cub);
	mlx_hook(cub->win, 2, (1L << 0), handle_key_press, cub);
	mlx_hook(cub->win, 3, (1L << 1), handle_key_release, cub);
	mlx_hook(cub->win, EVT_RED_CROSS, (1L << 2), ft_red_cross, cub);
	mlx_loop_hook(cub->mlx, ft_refresh, cub);
	mlx_loop(cub->mlx);
}

int			main(int ac, char **av)
{
	t_cub cub;

	if (ac >= 2 && ac <= 3)
	{
		ft_putendl(ENV_MSG);
		init_cub(&cub);
		cub_parser(ac, av, &cub);
		if (cub.save_opt && ft_save(&cub))
			return (0);
		else if (cub.save_opt)
			ft_error("Enable to create the .bmp file", &cub, NULL, 0);
		ft_mlx_start(&cub);
	}
	else
		ft_error("Arguments error", NULL, __FILE__, __LINE__);
	return (0);
}
