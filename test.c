/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:07:33 by besellem          #+#    #+#             */
/*   Updated: 2020/12/14 19:35:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*xpm_ptr;
	int		w;
	int		h;

	if (ac != 2)
	{
		ft_putendl_fd("args Error", 2);
		return (1);
	}
	mlx_ptr = mlx_init();
	if (!(xpm_ptr = mlx_xpm_file_to_image(mlx_ptr, av[1], &w, &h)))
	{
		ft_putendl_fd("malloc() Error", 2);
		return (1);
	}
	ft_printf("w: %d, h: %d\n", w, h);
	mlx_win = mlx_new_window(mlx_ptr, 320, 200, "TEST");
	mlx_put_image_to_window(mlx_ptr, mlx_win, xpm_ptr, 320, 200);
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
	free(mlx_win);
	free(xpm_ptr);
	return (0);
}
