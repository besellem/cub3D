# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2020/12/14 10:42:56 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE	=	@
NAME	=	Cub3D

## Sources
INCS	=	incs

# To change
SRCS	=	srcs/*.c

## Commands
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
RM		=	rm -f


$(NAME):
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(CC) $(CFLAGS) -o $(NAME) main.c $(SRCS) -I incs libft/libft.a

all:		$(NAME)

bonus:		all

test:		$(NAME)
			$(MUTE) $(CC) $(CFLAGS) -o $(NAME) main.c $(SRCS) -I incs libft/libft.a -L mlx/

clean:
			$(MUTE) $(MAKE) -C libft clean

fclean:		clean
			$(MUTE) $(MAKE) -C libft fclean
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all bonus test clean fclean re
