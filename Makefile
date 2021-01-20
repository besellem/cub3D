# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2021/01/20 09:58:39 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE		=	
NAME		=	cub3D
BMP_FILE	=	./saved.bmp

## Sources
INCS		=	incs libft/libft.a
MLIBX		=	libmlx.dylib

# To change
SRCS		=	main.c srcs/*.c

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
RM			=	rm -f
RMRF		=	rm -rf

# Get system name
UNAME		:=	$(shell uname)

## Targets
# Check system -- macOS or Linux -- & compilation
ifeq ($(UNAME), Darwin)
$(NAME):
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx all
			$(MUTE) cp ./mlx/$(MLIBX) .
			$(MUTE) $(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit -I $(INCS)
endif

ifeq ($(UNAME), Linux)
$(NAME):
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx_linux all
			$(MUTE) $(CC) $(CFLAGS) -I/usr/include -Imlx_linux $(SRCS) -Imlx_linux -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -I $(INCS) -o $(NAME)
endif

all:		$(NAME)

bonus:		all

test:		$(NAME)

ifeq ($(UNAME), Darwin)
clean:
			$(MUTE) $(MAKE) -C libft clean
			$(MUTE) $(MAKE) -C mlx clean
			# To remove along with the -g flag at compilation
			$(MUTE) $(RMRF) Cub3D.dSYM
			$(MUTE) $(RM) $(BMP_FILE)
endif

ifeq ($(UNAME), Linux)
clean:
			$(MUTE) $(MAKE) -C libft clean
			$(MUTE) $(MAKE) -C mlx_linux clean
			# To remove along with the -g flag at compilation
			$(MUTE) $(RMRF) Cub3D.dSYM
			$(MUTE) $(RM) $(BMP_FILE)
endif

fclean:		clean
			$(MUTE) $(MAKE) -C libft fclean
			$(MUTE) $(RM) $(MLIBX)
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all bonus test clean fclean re
