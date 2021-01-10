/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:56:20 by besellem          #+#    #+#             */
/*   Updated: 2021/01/10 13:45:55 by besellem         ###   ########.fr       */
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
# define TEXTURES_COUNT 5

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

# define HIT_NORTH 0
# define HIT_SOUTH 1
# define HIT_EAST 2
# define HIT_WEST 3

/*
** 2 * PI
*/
# define M_2PI 6.28318530717958623199592693708837032

/*
** FOV (field of view)
*/
# define FOV 90

/*
** Colors (for testing - to remove)
*/
# define UCOLOR_GREY 0xE0E0E0
# define UCOLOR_BLACK 0x0
# define UCOLOR_BLUE 0x8080FF
# define UCOLOR_RED 0xFF0000

/*
** Key mapping for macOS & Linux envs
*/
# if defined(__APPLE__) && defined(__MACH__)
#  define ENV_MSG "\033[1;32m[macOS environnement]\033[0m"
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define EVT_RED_CROSS 17
# else
#  define ENV_MSG "\033[1;32m[Linux (default) environnement]\033[0m"
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define EVT_RED_CROSS 33
# endif

/*
** -- STRUCTURES --
*/
typedef struct	s_map_checker
{
	int got_player_pos;
}				t_map_checker;

/*
** angle:		angle of the ray in radians
** is_down:		is the angle pointing up (0) or down (1)
** is_right:	is the angle pointing left (0) or right (1)
** xintcpt:		next cube from cub->pos_x
** yintcpt:		next cube from cub->pos_y
** xstep:		increment with xstep to check if we hit something
** ystep:		increment with ystep to check if we hit something
** distance:	distance from the player to a wall for that angle
** distortion:	cos(ray->angle - cub->drxion) -> is used 2 times per ray
** hit_wall_x:	coordinate x of the wall hit
** hit_wall_y:	coordinate y of the wall hit
** hit_drxion:	from where the ray hit a wall. Defined with macros NORTH, ...
*/
typedef struct	s_ray
{
	double	angle;
	double	xintcpt;
	double	yintcpt;
	double	xstep;
	double	ystep;
	double	distance;
	double	hit_wall_x;
	double	hit_wall_y;
	double	hit_sp_x;
	double	hit_sp_y;
	double	sp_distance;
	double	distortion;
	int		is_down;
	int		is_right;
	int		hit_vertical;
	int		hit_drxion;
}				t_ray;

typedef	struct	s_sprite
{
	double	x;
	double	y;
	int		hit;
}				t_sprite;

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
	int		x;
	int		y;
}				t_img;

/*
** win_w:			resolution width (if > screen, is troncated)
** win_h:			resolution heigh (if > screen, is troncated)
** parsed_width:	resolution width from the .cub file
** parsed_heigh:	resolution heigh from the .cub file
** sky_color:		sky color
** grnd_color:		ground color
** txtr_no:			path to the north texture file
** txtr_so:			path to the south texture file
** txtr_ea:			path to the east texture file
** txtr_we:			path to the west texture file
** txtr_s:			path to the sprite texture file
** map:				map
** map_size_x:		horizontal size of the map
** map_size_y:		vertical size of the map
** mlx:				pointer created by mlx_init()
** win:				pointer of the window
** drxion:			direction of the player in radians
** turn:			(key press): none (0), left angle (-1), right angle (1)
** dw:				(key press): none (0), left (-1), right (1)
** dh:				(key press): none (0), down (-1), up (1)
** pos_x:			player position horizontally
** pos_y:			player position vertically
** increment:		player's speed
** dist_plane:		distance to the projection plane
** cub_size:		size of a cube in pixels (for the minimap only)
** img:				image to print out
** txtrs:			all the textures and their infos
*/
typedef	struct	s_cub
{
	int		win_w;
	int		win_h;
	int		parsed_width;
	int		parsed_heigh;
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
	double	pos_x;
	double	pos_y;
	double	increment;
	double	dist_plane;
	int		cub_size;
	int		turn;
	int		dw;
	int		dh;
	t_keys	*keys;
	t_img	*img;
	t_img	*txtrs;
	t_ray	*rays;
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
double			get_dist(double x1, double y1, double x2, double y2);
double			get_dec(double n);
int				safe_min(int nb1, int nb2);

/*
** Utils
*/
void			print_specs(t_cub *cub);
void			print_map(t_cub *cub);

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
void			ft_pixel_put(t_cub *cub, int x, int y, unsigned int color);
void			cast_all_rays(t_cub *cub);
void			update_cubs(t_cub *cub);
void			update_minimap(t_cub *cub);
void			update_view(t_cub *cub);
int				ft_refresh(t_cub *cub);

/*
** Main
*/
int				init_cub(t_cub *cub);

#endif
