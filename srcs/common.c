/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:45:35 by besellem          #+#    #+#             */
/*   Updated: 2020/12/22 01:45:55 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *err, t_cub *cub, char *file, int line)
{
	if (cub)
		ft_free_cub(cub);
	ft_putendl_fd(CUB_ERR, 2);
	if (file && line > 0)
		ft_dprintf(2, B_YELLOW"%s:%d: "CLR_COLOR, file, line);
	else if (file && line <= 0)
		ft_dprintf(2, B_YELLOW"%s: "CLR_COLOR, file);
	else if (!file && line > 0)
		ft_dprintf(2, B_YELLOW"line %d: "CLR_COLOR, line);
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	ft_quit(t_cub *cub)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	mlx_destroy_window(cub->mlx, cub->win);
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

int		ft_red_cross(t_cub *cub)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_strs_size(char **strs)
{
	int i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		++i;
	return (i);
}

void	ft_free_strs(char **strs)
{
	int i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}
