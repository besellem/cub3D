/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2020/12/14 15:19:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TO REMOVE
void		print_specs(t_specs *specs)
{
	ft_printf("{\n");
	ft_printf("    specs->res_width: %d\n", specs->res_width);
	ft_printf("    specs->res_heigh: %d\n", specs->res_heigh);
	ft_printf("    specs->color_sky: %ld\n", specs->color_sky);
	ft_printf("    specs->color_ground: %ld\n", specs->color_ground);
	ft_printf("    specs->texture_north: %d\n", specs->texture_north);
	ft_printf("    specs->texture_south: %d\n", specs->texture_south);
	ft_printf("    specs->texture_east: %d\n", specs->texture_east);
	ft_printf("    specs->texture_west: %d\n", specs->texture_west);
	ft_printf("    specs->texture_sprite: %d\n", specs->texture_sprite);
	ft_printf("}\n");
}
// END

static void	init_specs(t_specs *specs)
{
	specs->res_width = -1;
	specs->res_heigh = -1;
	specs->color_ground = -1;
	specs->color_sky = -1;
}

static void	init_mlx(t_mlx_infos *mlx, t_specs *specs)
{
	mlx->mlx_ptr = mlx_init();
	// mlx_get_screen_size(mlx->mlx_ptr, &(specs->res_width), &(specs->res_heigh));
	print_specs(specs);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, specs->res_width, specs->res_heigh, NAME);

	int i = -1;
	int j;
	while (++i < specs->res_heigh / 2)
	{
		j = -1;
		while (++j < specs->res_width)
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, j, i, 0xff0000);
	}
	mlx_loop(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx->win_ptr);
}

int			main(int ac, char **av)
{
	t_specs		specs;
	t_mlx_infos	mlx;

	if (ac >= 2 && ac <= 3)
	{
		init_specs(&specs);

		(&specs)->res_width = 720;
		(&specs)->res_heigh = 480;
		// cub_parser(av[1], &specs);

		init_mlx(&mlx, &specs);
		/*
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
			if (cub_img_save(&specs))
				ft_error("Enable to save the image", NULL, 0);
		else if (ac == 3)
			ft_error("Argument error", NULL, 0);
		*/
		free(specs.map);
	}
	else
		ft_error("Arguments error", __FILE__, __LINE__);
	return (0);
}
