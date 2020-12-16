/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:07:33 by besellem          #+#    #+#             */
/*   Updated: 2020/12/15 23:40:42 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Structures
*/
typedef struct	s_keys
{
	int		key;
	void	(*f)();
}				t_keys;

typedef struct	s_cub
{
	void	*mlx;
	void	*win;
	double	pos_x;
	double	pos_y;
	double	inc;
	t_keys	*keys;
}				t_cub;

/*
** Functions
*/
void	ft_quit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->keys);
	free(cub->mlx);
	exit(EXIT_SUCCESS);
}

void	ft_key_left(t_cub *cub)
{
	ft_putendl("Move camera left");
	(void)cub;
}

void	ft_key_right(t_cub *cub)
{
	ft_putendl("Move camera right");
	(void)cub;
}

void	ft_move_front(t_cub *cub)
{
	cub->pos_y += cub->inc;
}

void	ft_move_back(t_cub *cub)
{
	cub->pos_y -= cub->inc;
}

void	ft_move_left(t_cub *cub)
{
	cub->pos_x -= cub->inc;
}

void	ft_move_right(t_cub *cub)
{
	cub->pos_x += cub->inc;
}

void	update_view(t_cub *cub)
{
	int x;
	int y;

	x = (int)cub->pos_x;
	y = (int)cub->pos_y;
	ft_printf("[ %f ; %f ]\n", cub->pos_x, cub->pos_y);
	mlx_pixel_put(cub->mlx, cub->win, x, y, 0xFFFFFF);
}

int		handle_key_event(int key, t_cub *cub)
{
	int i;

	i = -1;
	while (cub->keys[++i].f != NULL)
	{
		if (cub->keys[i].key == key)
		{
			ft_printf("key: [%d] [%p]\n", cub->keys[i].key, cub->keys[i].f);
			cub->keys[i].f(cub);
			update_view(cub);
			break ;
		}
	}
	return (0);
}

void	add_key(t_keys *keys, int key, void (*f)())
{
	keys->key = key;
	keys->f = f;
}

/*
** There are 7 keys to map 
*/
int		init_keys(t_cub *cub)
{
	int i;

	i = 0;
	if (!(cub->keys = (t_keys *)malloc(sizeof(t_keys) * (7 + 1))))
		return (1);
	add_key(&(cub->keys[i++]), KEY_LEFT, &ft_key_left);
	add_key(&(cub->keys[i++]), KEY_RIGHT, &ft_key_right);
	add_key(&(cub->keys[i++]), KEY_W, &ft_move_front);
	add_key(&(cub->keys[i++]), KEY_S, &ft_move_back);
	add_key(&(cub->keys[i++]), KEY_A, &ft_move_left);
	add_key(&(cub->keys[i++]), KEY_D, &ft_move_right);
	add_key(&(cub->keys[i++]), KEY_ESC, &ft_quit);
	add_key(&(cub->keys[i]), -1, NULL);
	return (0);
}

int		init_cub(t_cub *cub)
{
	if (init_keys(cub))
		return (1);
	cub->pos_x = 0.0;
	cub->pos_y = 0.0;
	cub->inc = 10.0;
	return (0);
}

int		main(int ac, char **av)
{
	t_cub	cub;

	if (KEY_ESC != -1)
		ft_putendl(B_GREEN"[macOS environnement]"CLR_COLOR);
	else
		ft_putendl(B_GREEN"[Linux (or default) environnement]"CLR_COLOR);

	if (init_cub(&cub))
	{
		// ft_error("Malloc error", __FILE__, __LINE__);
		ft_putendl_fd("Malloc error", 2);
		exit(EXIT_FAILURE);
	}
	(void)ac;
	(void)av;
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, 480, 320, "test");
	mlx_do_key_autorepeaton(cub.mlx);
	mlx_key_hook(cub.win, handle_key_event, &cub);
	
	// mlx_pixel_put(cub.mlx, cub.win, (int)cub.pos_x, (int)cub.pos_y, 0xFFFFFF);
	mlx_loop(cub.mlx);

	/*
	void	*xpm_ptr;
	int		w;
	int		h;

	if (ac != 2)
	{
		ft_putendl_fd("args Error", 2);
		return (1);
	}
	conf.mlx = mlx_init();
	if (!(xpm_ptr = mlx_xpm_file_to_image(conf.mlx, av[1], &w, &h)))
	{
		ft_putendl_fd("malloc() Error", 2);
		return (1);
	}
	ft_printf("w: %d, h: %d\n", w, h);
	conf.win = mlx_new_window(conf.mlx, 320, 200, "TEST");
	void *new_img = mlx_new_image(conf.mlx, 320, 200);
	mlx_put_image_to_window(conf.mlx, conf.win, xpm_ptr, 320, 200);
	mlx_loop(conf.mlx);
	free(conf.mlx);
	free(conf.win);
	free(xpm_ptr);
	*/
	return (0);
}
