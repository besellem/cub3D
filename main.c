/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2021/01/11 15:28:03 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_start(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, NAME);
	cub->img->ptr = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	cub->img->addr = mlx_get_data_addr(cub->img->ptr,
										&(cub->img->bits_per_pixel),
										&(cub->img->size_line),
										&(cub->img->endian));
	update_view(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->ptr, 0, 0);
	print_specs(cub);
	mlx_hook(cub->win, 2, (1L << 0), handle_key_press, cub);
	mlx_hook(cub->win, 3, (1L << 1), handle_key_release, cub);
	mlx_hook(cub->win, EVT_RED_CROSS, (1L << 2), ft_red_cross, cub);
	mlx_loop_hook(cub->mlx, ft_refresh, cub);
	mlx_loop(cub->mlx);
}

static void	write_file(t_cub *cub, int fd)
{
	unsigned int	nbr;

	write(fd, "BM", 2);
	nbr = cub->img->bits_per_pixel * cub->parsed_h * cub->parsed_w;
	write(fd, &nbr, 4);
	nbr = 0x0;
	write(fd, &nbr, 4);
}

static int	ft_save(t_cub *cub)
{
	int fd;

	cub->img->ptr = mlx_new_image(cub->mlx, cub->parsed_w, cub->parsed_h);
	cub->img->addr = mlx_get_data_addr(cub->img->ptr,
										&(cub->img->bits_per_pixel),
										&(cub->img->size_line),
										&(cub->img->endian));
	update_view(cub);
	print_specs(cub);
	if ((fd = open(BMP_FILEPATH, O_WRONLY | O_CREAT, 0644)) == 1)
		return (0);
	write_file(cub, fd);
	close(fd);
	ft_free_cub(cub);
	ft_printf("BMP file created -> "B_GREEN"%s\n"CLR_COLOR, BMP_FILEPATH);
	return (1);
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
		if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
		{
			if (!ft_save(&cub))
				ft_error("Enable to create the .bmp file", &cub, NULL, 0);
			return (0);
		}
		else if (ac == 3)
			ft_error("Argument error", &cub, NULL, 0);
		ft_mlx_start(&cub);
	}
	else
		ft_error("Arguments error", NULL, __FILE__, __LINE__);
	return (0);
}
