# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2020/12/14 15:12:28 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE	=	@
NAME	=	Cub3D

## Sources
INCS	=	incs libft/libft.a

# To change
SRCS	=	main.c srcs/*.c

## Commands
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -L /usr/X11/lib -lX11 -lmlx -lXext
RM		=	rm -f

$(NAME):
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(CC) -o $(NAME) -I /usr/local/include $(SRCS) -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -I incs libft/libft.a

all:		$(NAME)

bonus:		all

test:		$(NAME)

clean:
			$(MUTE) $(MAKE) -C libft clean

fclean:		clean
			$(MUTE) $(MAKE) -C libft fclean
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all bonus test clean fclean re
