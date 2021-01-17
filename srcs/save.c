/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:33:49 by besellem          #+#    #+#             */
/*   Updated: 2021/01/17 13:47:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_cursor(t_uint64 current, t_uint64 max)
{
	t_uint64 line_length;
	t_uint64 i;

	line_length = 30;
	i = -1;
	ft_putstr(CLR_LINE);
	write(1, "[", 1);
	while (++i < ((double)current / max) * line_length)
		write(1, "#", 1);
	while (i++ < line_length)
		write(1, " ", 1);
	write(1, "] ", 2);
	ft_printf("%.2f %%", ((double)current / max) * 100);
}

static void	ft_bmp_header(t_cub *cub, int fd)
{
	t_uint64 nb;

	write(fd, "BM", 2);
	nb = cub->img->bits_per_pixel * cub->parsed_h * cub->parsed_w + 54 * 8;
	ft_printf("# Generating "B_GREEN"%s"CLR_COLOR" (%.2f mb) ...\n",
			BMP_FILEPATH, (double)nb / 8000000);
	write(fd, &nb, 4);
	nb = 0;
	write(fd, &nb, 4);
	nb = 54;
	write(fd, &nb, 4);
}

static void	ft_bmp_dib_header(t_cub *cub, int fd)
{
	t_uint64	nb;
	int			i;

	nb = 40;
	write(fd, &nb, 4);
	write(fd, &cub->parsed_w, 4);
	write(fd, &cub->parsed_h, 4);
	nb = 1;
	write(fd, &nb, 2);
	write(fd, &cub->img->bits_per_pixel, 2);
	nb = 0;
	i = -1;
	while (++i < 6)
		write(fd, &nb, 4);
}

static void	ft_bmp_pixel_array(t_cub *cub, int fd)
{
	t_img	*img;
	char	*ptr;
	char	*addr;
	int		i;
	int		j;

	img = cub->img;
	addr = img->addr;
	i = cub->parsed_h;
	while (i-- > 0)
	{
		j = -1;
		while (++j < cub->parsed_w)
		{
			ptr = addr + i * img->size_line + j * (img->bits_per_pixel / 8);
			write(fd, &(*(t_uint32 *)ptr), 4);
		}
		update_cursor(cub->parsed_h - i, cub->parsed_h);
	}
	write(1, "\n", 1);
}

int			ft_save(t_cub *cub)
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
	ft_bmp_header(cub, fd);
	update_cursor(0, cub->parsed_h);
	ft_bmp_dib_header(cub, fd);
	ft_bmp_pixel_array(cub, fd);
	close(fd);
	ft_free_cub(cub);
	ft_putendl(B_GREEN"Done !"CLR_COLOR);
	return (1);
}
