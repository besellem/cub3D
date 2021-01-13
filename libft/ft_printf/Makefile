# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 21:13:07 by besellem          #+#    #+#              #
#    Updated: 2021/01/12 23:08:57 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE		=	
NAME		=	libftprintf.a

## Mandatory
INCS		=	inc/ft_printf.h

SRCS		+=	srcs/ft_common.c
SRCS		+=	srcs/ft_common2.c
SRCS		+=	srcs/ft_common3.c
SRCS		+=	srcs/ft_lst_common.c
SRCS		+=	srcs/ft_lst_common2.c
SRCS		+=	srcs/ft_init_conversions.c
SRCS		+=	srcs/ft_parser.c
SRCS		+=	srcs/ft_specifiers.c
SRCS		+=	srcs/ft_alloc_txt.c
SRCS		+=	srcs/ft_alloc_format.c
SRCS		+=	srcs/ft_format_checks.c
SRCS		+=	srcs/ft_format_checks2.c
SRCS		+=	srcs/ft_alloc_mod.c
SRCS		+=	srcs/ft_alloc_c.c
SRCS		+=	srcs/ft_alloc_s.c
SRCS		+=	srcs/ft_alloc_p.c
SRCS		+=	srcs/ft_alloc_idu.c
SRCS		+=	srcs/ft_alloc_hex.c
SRCS		+=	srcs/ft_alloc_f.c
SRCS		+=	srcs/ft_alloc_f_utils.c
SRCS		+=	srcs/ft_alloc_n.c
SRCS		+=	srcs/ft_alloc_o.c
SRCS		+=	srcs/ft_alloc_b.c

SRCS		+=	family/ft_printf.c
SRCS		+=	family/ft_sprintf.c
SRCS		+=	family/ft_snprintf.c
SRCS		+=	family/ft_asprintf.c
SRCS		+=	family/ft_dprintf.c
SRCS		+=	family/ft_vprintf.c
SRCS		+=	family/ft_vsprintf.c
SRCS		+=	family/ft_vsnprintf.c
SRCS		+=	family/ft_vasprintf.c
SRCS		+=	family/ft_vdprintf.c

## Objects
OBJS		=	$(SRCS:.c=.o)

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
LIBC		=	ar rc
RM			=	rm -f

.c.o:
			$(MUTE) $(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCS)

$(NAME):	$(OBJS)
			$(MUTE) $(LIBC) $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(MUTE) $(RM) $(OBJS)

fclean:		clean
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all clean fclean re
