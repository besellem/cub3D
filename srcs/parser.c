/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2020/12/17 02:12:56 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		are_specs_complete(t_cub *cub)
{
	if (cub->grnd_color != -1 && cub->sky_color != -1 &&
		cub->win_h != -1 && cub->win_w != -1 &&
		cub->txtr_no && cub->txtr_so && cub->txtr_ea &&
		cub->txtr_we && cub->txtr_s)
		return (1);
	return (0);
}

void	cub_parser(char *file, t_cub *cub)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1 ||
		ft_strcmp(file + (ft_strlen(file) - 4), ".cub") != 0)
	{
		ft_putendl_fd(CUB_ERR, 2);
		perror(file);
		exit(EXIT_FAILURE);
	}
	cub_fill_specs(fd, cub);
	parse_map(fd, cub);
	print_map(cub);
	close(fd);
}
