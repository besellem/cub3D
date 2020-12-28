/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:56:20 by besellem          #+#    #+#             */
/*   Updated: 2020/12/28 20:22:22 by besellem         ###   ########.fr       */
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
** Get the 4 cardinal values whithin a circle:
**            N (PI / 2)
**            |
**            |
** W (PI) ---- ---- E (0.0)
**            |
**            |
**            S (PI + (PI / 2) OR (3 * PI) / 2)
*/
# define DRXION_E 0.0
# define DRXION_N M_PI_2
# define DRXION_W M_PI
# define DRXION_S 4.71238898038468967399694520281627774

/*
** FOV (field of view)
*/
# define FOV 90

# define UCOLOR_GREY 0xE0E0E0
# define UCOLOR_BLACK 0x0
# define UCOLOR_BLUE 0x8080ff
# define UCOLOR_RED 0xFF0000

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
typedef struct	s_map_checker
{
	int got_player_pos;
}				t_map_checker;

typedef struct	s_ray
{
	double	angle;
	char	is_down;
	char	is_right;
	double	xintcpt;
	double	yintcpt;
	double	xstep;
	double	ystep;
	double	distance;
	double	hit_wall_x;
	double	hit_wall_y;
}				t_ray;

typedef struct	s_keys
{
	int key_w;
	int key_s;
	int key_a;
	int key_d;
	int key_left;
	int key_right;
}				t_keys;

typedef struct	s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef	struct	s_cub
{
	int		win_w;
	int		win_h;
	int		sky_color;
	int		grnd_color;
	char	*txtr_no;
	char	*txtr_so;
	char	*txtr_ea;
	char	*txtr_we;
	char	*txtr_s;
	char	**map;
	size_t	map_size_x;
	size_t	map_size_y;
	void	*mlx;
	void	*win;
	double	drxion;
	int		turn;
	int		dw;
	int		dh;
	double	pos_x;
	double	pos_y;
	double	increment;
	int		cub_size;
	t_keys	*keys;
	t_img	*img;
}				t_cub;

/*
** -- PROTOTYPES --
** Common
*/
void			ft_error(char *err, t_cub *cub, char *file, int line);
void			ft_quit(t_cub *cub);
int				ft_red_cross(t_cub *cub);
void			ft_free_cub(t_cub *cub);
void			ft_free_strs(char **strs);
int				ft_strs_size(char **strs);
int				file_got_ext(char *file, char *extension);
int				in_charset(char *charset, int c);
int				charset_in_line(char *line, char *charset);
int				is_rgb(int color);
long			ft_rgb(unsigned char r, unsigned char g, unsigned char b);
double			ft_deg2rad(int deg);
double			ft_rad2deg(double rad);
double			ft_norm_angle(double angle);

/*
** Utils
*/
void			print_specs(t_cub *cub);
void			print_map(t_cub *cub);
void			ft_get_env(void);

/*
** Parser & Checkers
*/
int				are_specs_complete(t_cub *cub);
void			cub_fill_specs(int fd, t_cub *cub);
void			parse_map(int fd, t_cub *cub);
int				check_map(t_cub *cub);
void			cub_parser(char *file, t_cub *cub);

/*
** Events handlers
*/
int				handle_key_press(int key, t_cub *cub);
int				handle_key_release(int key, t_cub *cub);

/*
** Display
*/
void			update_view(t_cub *cub);

/*
** Main
*/
int				init_cub(t_cub *cub);

#endif
