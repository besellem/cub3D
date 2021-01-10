# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2021/01/11 00:06:17 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE		=	
NAME		=	Cub3D
BMP_FILE	=	./saved.bmp

## Sources
INCS		=	incs libft/libft.a
MLIBX		=	libmlx.dylib

# To change
SRCS		=	main.c srcs/*.c

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror# -fsanitize=address #Check leak option in Linux
RM			=	rm -f
RMD			=	rm -rf

$(NAME):
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx all
			$(MUTE) cp ./mlx/$(MLIBX) .
			$(MUTE) $(CC) $(CFLAGS) -g3 -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit -I $(INCS)

all:		$(NAME)

bonus:		all

test:		$(NAME)

clean:
			$(MUTE) $(MAKE) -C libft clean
			$(MUTE) $(MAKE) -C mlx clean
			$(MUTE) $(RMD) Cub3D.dSYM
			$(MUTE) $(RM) $(BMP_FILE)

fclean:		clean
			$(MUTE) $(MAKE) -C libft fclean
			$(MUTE) $(RM) $(MLIBX)
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all bonus test clean fclean re
