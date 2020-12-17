/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2020/12/17 02:08:42 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub cub;

	if (ac >= 2 && ac <= 3)
	{
		ft_get_env();
		if (init_cub(&cub))
			ft_error("Malloc err while initializing", &cub, __FILE__, __LINE__);

		cub_parser(av[1], &cub);
		/*
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
			if (cub_img_save(&cub))
				ft_error("Enable to save the image", &cub, NULL, 0);
		else if (ac == 3)
			ft_error("Argument error", &cub, NULL, 0);
		*/
		cub.mlx = mlx_init();
		cub.win = mlx_new_window(cub.mlx, cub.win_w, cub.win_h, NAME);
		mlx_do_key_autorepeaton(cub.mlx);
		mlx_key_hook(cub.win, handle_key_event, &cub);
		update_view(&cub);
		print_specs(&cub); // TO REMOVE
		mlx_loop(cub.mlx);
	}
	else
		ft_error("Arguments error", NULL, __FILE__, __LINE__);
	return (0);
}
