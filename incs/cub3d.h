/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:56:20 by besellem          #+#    #+#             */
/*   Updated: 2020/12/16 01:07:43 by besellem         ###   ########.fr       */
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
# define NAME "Cub3D"
# define CUB_ERR "\033[1;31mError\033[0m"
# define MAP_CHARSET " 012NEWS"

/*
** FOV (field of view)
*/
# define FOV 60

/*
** Key mapping for macOS & Linux envs
** For macOS compilation	=> cc ... -D MACOS_WORKSTATION ...
** For Linux:				=> compile normally
*/
# ifdef MACOS_WORKSTATION
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
# else
#  define KEY_ESC -1
#  define KEY_LEFT -1
#  define KEY_RIGHT -1
#  define KEY_W -1
#  define KEY_A -1
#  define KEY_S -1
#  define KEY_D -1
# endif

/*
** -- STRUCTURES --
*/
typedef struct	s_keys
{
	int		key;
	void	(*f)();
}				t_keys;

typedef	struct	s_cub
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	int		sky_color;
	int		grnd_color;
	int		txtr_no;
	int		txtr_so;
	int		txtr_ea;
	int		txtr_we;
	int		txtr_s;
	char	**map;
	double	pos_x;
	double	pos_y;
	double	increment;
	t_keys	*keys;
}				t_cub;

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
** Main
*/
int				init_cub(t_cub *cub);

/*
** Parser & Checkers
*/
int				are_specs_complete(t_cub *cub);
void			cub_fill_specs(int fd, t_cub *cub);
void			cub_parser(char *file, t_cub *cub);

/*
** Events handlers
*/
void			ft_quit(t_cub *cub);
void			ft_key_left(t_cub *cub);
void			ft_key_right(t_cub *cub);
void			ft_move_front(t_cub *cub);
void			ft_move_back(t_cub *cub);
void			ft_move_left(t_cub *cub);
void			ft_move_right(t_cub *cub);
int				handle_key_event(int key, t_cub *cub);

/*
** Display
*/
void			update_view(t_cub *cub);

#endif
