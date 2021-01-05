/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2021/01/05 15:11:18 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	need_update(t_cub *cub)
{
	return (cub->dh != 0 || cub->dw != 0 || cub->turn != 0);
}

static int	ft_hook(t_cub *cub)
{
	if (need_update(cub))
		update_view(cub);
	return (0);
}

static void	ft_mlx_start(t_cub *cub)
{
	load_textures(cub);
	mlx_do_key_autorepeaton(cub->mlx);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, NAME);
	cub->img->ptr = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	cub->img->addr = mlx_get_data_addr(cub->img->ptr,
										&(cub->img->bits_per_pixel),
										&(cub->img->size_line),
										&(cub->img->endian));
	update_view(cub);
	print_specs(cub); // TO REMOVE
	mlx_hook(cub->win, 2, (1L << 0), handle_key_press, cub);
	mlx_hook(cub->win, 3, (1L << 1), handle_key_release, cub);
	mlx_hook(cub->win, 17, (1L << 2), ft_red_cross, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
}

static int	ft_save_img(t_cub *cub)
{
	(void)cub;
	return (0);
}

int			main(int ac, char **av)
{
	t_cub cub;

	if (ac >= 2 && ac <= 3)
	{
		ft_putendl(ENV_MSG);
		if (init_cub(&cub))
			ft_error("Malloc err while initializing", &cub, __FILE__, __LINE__);
		cub_parser(av[1], &cub);
		cub.mlx = mlx_init();
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
		{
			if (!ft_save_img(&cub))
				ft_error("Enable to save the image", &cub, NULL, 0);
		}
		else if (ac == 3)
			ft_error("Argument error", &cub, NULL, 0);
		ft_mlx_start(&cub);
	}
	else
		ft_error("Arguments error", NULL, __FILE__, __LINE__);
	return (0);
}
