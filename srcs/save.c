/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:33:49 by besellem          #+#    #+#             */
/*   Updated: 2021/01/12 16:00:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_bmp_header(t_cub *cub, int fd)
{
	t_uint64 nb;

	write(fd, "BM", 2);
	nb = (cub->img->bits_per_pixel / 8) * cub->parsed_h * cub->parsed_w * cub->img->size_line;
	ft_printf(B_RED"bmp_size: %u bits, %u bytes\n"CLR_COLOR, nb, nb / 8);
	write(fd, &nb, 4);
	nb = 0;
	write(fd, &nb, 4);
	nb = 54;
	write(fd, &nb, 4);
}

static void	ft_bmp_dib_header(t_cub *cub, int fd)
{
	t_uint64 nb;

	nb = 40;
	write(fd, &nb, 4);
	write(fd, &cub->parsed_w, 4);
	write(fd, &cub->parsed_h, 4);
	nb = 1;
	write(fd, &nb, 2);
	write(fd, &cub->img->bits_per_pixel, 2);
	nb = 0;
	write(fd, &nb, 24);
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
	}
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
	ft_bmp_dib_header(cub, fd);
	ft_bmp_pixel_array(cub, fd);
	close(fd);
	ft_free_cub(cub);
	ft_printf("BMP file created -> "B_GREEN"%s\n"CLR_COLOR, BMP_FILEPATH);
	return (1);
}
