/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:50:40 by besellem          #+#    #+#             */
/*   Updated: 2020/12/16 00:48:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_size_spec(char **split, t_cub *cub)
{
	int x_tmp;
	int y_tmp;

	if (ft_strs_size(split) != 3)
		ft_error("Bad resolution configuration", __FILE__, __LINE__);
	cub->win_w = ft_atoi(split[1]);
	cub->win_h = ft_atoi(split[2]);
	ft_free_strs(split);
	if (cub->win_w < 0 || cub->win_h < 0)
		ft_error("Bad resolution configuration", __FILE__, __LINE__);
	mlx_get_screen_size(cub->mlx, &x_tmp, &y_tmp);
	if (cub->win_w > x_tmp)
		cub->win_w = x_tmp;
	if (cub->win_h > y_tmp)
		cub->win_h = y_tmp;
}

/*
** The rgb variables are int type because we need to know if the rgb color
** from the config overflowed an unsigned char or not
*/

static void	color_specs(char where, char **split, t_cub *cub)
{
	long	color;
	int		r;
	int		g;
	int		b;

	if (ft_strs_size(split) != 3)
		ft_error("Bad color configuration", __FILE__, __LINE__);
	r = ft_atoi(split[0] + 2);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_strs(split);
	if (!(is_rgb(r) && is_rgb(g) && is_rgb(b)))
		ft_error("Bad color configuration", __FILE__, __LINE__);
	color = ft_rgb(r, g, b);
	if (where == 'F' && cub->grnd_color == -1)
		cub->grnd_color = color;
	else if (where == 'C' && cub->sky_color == -1)
		cub->sky_color = color;
	else
		ft_error("Bad color configuration", __FILE__, __LINE__);
}

int			is_fd_open(int fd, t_cub *cub)
{
	if (fd == cub->txtr_no || fd == cub->txtr_so ||
		fd == cub->txtr_ea || fd == cub->txtr_we ||
		fd == cub->txtr_s)
		return (1);
	return (0);
}

static void	texture_specs(char *line, t_cub *cub)
{
	char	**nfos;
	int		fd;

	nfos = ft_split(line, ' ');
	if (ft_strs_size(nfos) != 2)
		ft_error("Bad texture configuration", __FILE__, __LINE__);
	if ((fd = open(nfos[1], O_RDONLY)) == -1 && read(fd, NULL, 0))
		ft_error("Cannot open a texture file", __FILE__, __LINE__);
	if (!ft_strncmp(line, "NO ", 3) && cub->txtr_no == -1)
		cub->txtr_no = fd;
	else if (!ft_strncmp(line, "SO ", 3) && cub->txtr_so == -1)
		cub->txtr_so = fd;
	else if (!ft_strncmp(line, "WE ", 3) && cub->txtr_we == -1)
		cub->txtr_we = fd;
	else if (!ft_strncmp(line, "EA ", 3) && cub->txtr_ea == -1)
		cub->txtr_ea = fd;
	else if (!ft_strncmp(line, "S ", 2) && cub->txtr_s == -1)
		cub->txtr_s = fd;
	else
	{
		ft_free_strs(nfos);
		ft_error("Doublons in texture configuration", __FILE__, __LINE__);
	}
	ft_free_strs(nfos);
}

static void	check_line(char *line, t_cub *cub, int *specs_completed)
{
	if (!ft_strncmp(line, "R ", 2))
		window_size_spec(ft_split(line, ' '), cub);
	else if (!ft_strncmp(line, "F ", 2))
		color_specs('F', ft_split(line, ','), cub);
	else if (!ft_strncmp(line, "C ", 2))
		color_specs('C', ft_split(line, ','), cub);
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		texture_specs(line, cub);
	else if (are_specs_complete(cub))
		*specs_completed = 1;
}

void		cub_fill_specs(int fd, t_cub *cub)
{
	char	*ret;
	int		check;
	int		specs_completed;

	specs_completed = 0;
	while ((check = get_next_line(fd, &ret)) >= 0)
	{
		check_line(ret, cub, &specs_completed);
		free(ret);
		if (specs_completed == 1)
			break ;
		if (check == 0)
			ft_error("Incomplete configuration", __FILE__, __LINE__);
	}
}
