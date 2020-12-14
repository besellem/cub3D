/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:56:20 by besellem          #+#    #+#             */
/*   Updated: 2020/12/14 17:38:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** -- INCLUDES --
*/
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

/*
** -- DEFINES --
*/
/*
** FOV	=>	field of view
** H_FOV:	horizontal
** V_FOV:	vertical		=>	Not sure if we need this one yet
*/
# define NAME "Cub3D"
# define CUB_ERR B_RED"Error"CLR_COLOR

# define H_FOV 60
# define V_FOV 100

# define MAP_CHARSET "012NEWS"

/*
** -- STRUCTURES --
*/
typedef	struct	s_specs
{
	int		res_width;
	int		res_heigh;
	long	color_sky;
	long	color_ground;
	int		texture_north;
	int		texture_south;
	int		texture_east;
	int		texture_west;
	int		texture_sprite;
	char	**map;
}				t_specs;

typedef struct	s_mlx_infos
{
	void *mlx_ptr;
	void *win_ptr;
}				t_mlx_infos;

/*
** -- PROTOTYPES --
** Common
*/
void			ft_error(char *err, char *file, int line);
void			ft_free_strs(char **strs);
int				ft_strs_size(char **strs);
int				is_rgb(int color);
long			ft_rgb(unsigned char r, unsigned char g, unsigned char b);

/*
** Parser & Checkers
*/
int				are_specs_complete(t_specs *specs);
void			cub_fill_specs(int fd, t_specs *specs);
void			cub_parser(char *file, t_specs *specs);

/*
** Display
*/

#endif
