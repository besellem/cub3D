/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:50:40 by besellem          #+#    #+#             */
/*   Updated: 2020/12/31 11:54:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_size_spec(char **split, t_cub *cub, int line_c)
{
	int x_tmp;
	int y_tmp;

	if (ft_strs_size(split) != 3)
		ft_error("Bad resolution configuration", cub, NULL, line_c);
	cub->parsed_width = ft_atoi(split[1]);
	cub->parsed_heigh = ft_atoi(split[2]);
	cub->win_w = cub->parsed_width;
	cub->win_h = cub->parsed_heigh;
	ft_free_strs(split);
	if (cub->win_w <= 0 || cub->win_h <= 0)
		ft_error("Bad resolution configuration", cub, NULL, line_c);
	mlx_get_screen_size(cub->mlx, &x_tmp, &y_tmp);
	if (cub->win_w > x_tmp)
		cub->win_w = x_tmp;
	if (cub->win_h > y_tmp)
		cub->win_h = y_tmp;
	if (!(cub->rays = (t_ray *)malloc(sizeof(t_ray) * cub->win_w)))
		ft_error("Malloc error", cub, __FILE__, line_c);
	cub->dist_plane = (cub->win_w / 2) / tan(FOV / 2);
}

/*
** The rgb variables are int type because we need to know if the rgb color
** from the config overflowed an unsigned char or not
*/

static void	color_specs(char where, char **split, t_cub *cub, int line_c)
{
	long	color;
	int		r;
	int		g;
	int		b;

	if (ft_strs_size(split) != 3)
		ft_error("Bad color configuration", cub, NULL, line_c);
	r = ft_atoi(split[0] + 2);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_strs(split);
	if (!(is_rgb(r) && is_rgb(g) && is_rgb(b)))
		ft_error("Bad color configuration", cub, NULL, line_c);
	color = ft_rgb(r, g, b);
	if (where == 'F' && cub->grnd_color == -1)
		cub->grnd_color = color;
	else if (where == 'C' && cub->sky_color == -1)
		cub->sky_color = color;
	else
		ft_error("Bad color configuration", cub, NULL, line_c);
}

static void	texture_specs(char *line, t_cub *cub, int line_c)
{
	char	**nfos;
	int		fd;

	nfos = ft_split(line, ' ');
	if (ft_strs_size(nfos) != 2)
		ft_error("Bad texture configuration", cub, NULL, line_c);
	if ((!file_got_ext(nfos[1], ".xpm") && !file_got_ext(nfos[1], ".png")) ||
		(fd = open(nfos[1], O_RDONLY)) == -1 || read(fd, NULL, 0) || close(fd))
		ft_error("Cannot open or read a texture file", cub, NULL, line_c);
	if (!ft_strncmp(line, "NO ", 3) && !cub->txtr_no)
		cub->txtr_no = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "SO ", 3) && !cub->txtr_so)
		cub->txtr_so = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "WE ", 3) && !cub->txtr_we)
		cub->txtr_we = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "EA ", 3) && !cub->txtr_ea)
		cub->txtr_ea = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "S ", 2) && !cub->txtr_s)
		cub->txtr_s = ft_strdup(nfos[1]);
	ft_free_strs(nfos);
}

static void	check_line(char *line, t_cub *cub, int *specs_completed, int line_c)
{
	if (!ft_strncmp(line, "R ", 2) && cub->win_w == -1 && cub->win_h == -1)
		window_size_spec(ft_split(line, ' '), cub, line_c);
	else if (!ft_strncmp(line, "F ", 2) && cub->grnd_color == -1)
		color_specs('F', ft_split(line, ','), cub, line_c);
	else if (!ft_strncmp(line, "C ", 2) && cub->sky_color == -1)
		color_specs('C', ft_split(line, ','), cub, line_c);
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) ||
			!ft_strncmp(line, "S ", 2))
		texture_specs(line, cub, line_c);
	else if (ft_strlen(line) > 0)
	{
		free(line);
		ft_error("Incomplete configuration", cub, NULL, line_c);
	}
	if (are_specs_complete(cub))
		*specs_completed = 1;
}

void		cub_fill_specs(int fd, t_cub *cub)
{
	char	*ret;
	int		check;
	int		line_count;
	int		specs_completed;

	line_count = 0;
	specs_completed = 0;
	while ((check = get_next_line(fd, &ret)) >= 0)
	{
		++line_count;
		check_line(ret, cub, &specs_completed, line_count);
		free(ret);
		if (specs_completed == 1)
			break ;
		if (check == 0)
			ft_error("Incomplete configuration", cub, NULL, line_count);
	}
}
