/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2020/12/10 00:58:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_specs(t_specs *specs)
{
	specs->res_width = -1;
	specs->res_heigh = -1;
	specs->color_ground = -1;
	specs->color_sky = -1;
}

int			main(int ac, char **av)
{
	t_specs specs;

	if (ac >= 2 && ac <= 3)
	{
		init_specs(&specs);
		cub_parser(av[1], &specs);
		/*
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
			if (cub_img_save(&specs))
				ft_error("Enable to save the image\n");
		else if (ac == 3)
			ft_error("Argument error\n");
		*/
	}
	return (0);
}
