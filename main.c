/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2020/12/16 00:59:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TO REMOVE
void		print_specs(t_cub *cub)
{
	ft_putendl("-- Specs --");
	ft_putendl("{");
	ft_printf("    cub->mlx:        %p\n", cub->mlx);
	ft_printf("    cub->win:        %p\n", cub->win);
	ft_printf("    cub->win_w:      %d\n", cub->win_w);
	ft_printf("    cub->win_h:      %d\n", cub->win_h);
	ft_printf("    cub->sky_color:  %ld\n", cub->sky_color);
	ft_printf("    cub->grnd_color: %ld\n", cub->grnd_color);
	ft_printf("    cub->txtr_no:    %d\n", cub->txtr_no);
	ft_printf("    cub->txtr_so:    %d\n", cub->txtr_so);
	ft_printf("    cub->txtr_ea:    %d\n", cub->txtr_ea);
	ft_printf("    cub->txtr_we:    %d\n", cub->txtr_we);
	ft_printf("    cub->txtr_s:     %d\n", cub->txtr_s);
	ft_printf("    cub->pos_x:      %d\n", cub->pos_x);
	ft_printf("    cub->pos_y:      %d\n", cub->pos_y);
	ft_printf("    cub->increment:  %d\n", cub->increment);
	ft_putendl("}");
	ft_putendl("----\n");
}

void	ft_get_env(void)
{
	if (KEY_ESC != -1)
		ft_putendl(B_GREEN"[macOS environnement]"CLR_COLOR);
	else
		ft_putendl(B_GREEN"[Linux (default) environnement]"CLR_COLOR);
}
// END

int			main(int ac, char **av)
{
	t_cub cub;

	if (ac >= 2 && ac <= 3)
	{
		ft_get_env();
		if (init_cub(&cub))
			ft_error("Malloc error", __FILE__, __LINE__);
		
		(void)av;
		cub.win_w = 1080;
		cub.win_h = 720;

		// cub_parser(av[1], &cub);

		cub.mlx = mlx_init();
		cub.win = mlx_new_window(cub.mlx, cub.win_w, cub.win_h, NAME);
		mlx_do_key_autorepeaton(cub.mlx);
		mlx_key_hook(cub.win, handle_key_event, &cub);
		
		// mlx_pixel_put(cub.mlx, cub.win, (int)cub.pos_x, (int)cub.pos_y, 0xFFFFFF);
		print_specs(&cub);
		
		mlx_loop(cub.mlx);
		
		/*
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
			if (cub_img_save(&cub))
				ft_error("Enable to save the image", NULL, 0);
		else if (ac == 3)
			ft_error("Argument error", NULL, 0);
		*/
	}
	else
		ft_error("Arguments error", __FILE__, __LINE__);
	return (0);
}
