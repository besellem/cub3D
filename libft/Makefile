# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/13 02:01:30 by besellem          #+#    #+#              #
#    Updated: 2021/01/13 13:06:08 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE		=	
NAME		=	libft.a

# Main srcs
SRCS		+=	ft_atod.c
SRCS		+=	ft_atoi_base.c
SRCS		+=	ft_atoi.c
SRCS		+=	ft_atol.c
SRCS		+=	ft_atold.c
SRCS		+=	ft_atoll.c
SRCS		+=	ft_bzero.c
SRCS		+=	ft_calloc.c
SRCS		+=	ft_factorial.c
SRCS		+=	ft_find_next_prime.c
SRCS		+=	ft_is_prime.c
SRCS		+=	ft_isalnum.c
SRCS		+=	ft_isalpha.c
SRCS		+=	ft_isascii.c
SRCS		+=	ft_isdigit.c
SRCS		+=	ft_isprint.c
SRCS		+=	ft_itoa_base.c
SRCS		+=	ft_itoa.c
SRCS		+=	ft_lstadd_back.c
SRCS		+=	ft_lstadd_front.c
SRCS		+=	ft_lstclear.c
SRCS		+=	ft_lstdelone.c
SRCS		+=	ft_lstiter.c
SRCS		+=	ft_lstlast.c
SRCS		+=	ft_lstmap.c
SRCS		+=	ft_lstnew.c
SRCS		+=	ft_lstsize.c
SRCS		+=	ft_memccpy.c
SRCS		+=	ft_memchr.c
SRCS		+=	ft_memcmp.c
SRCS		+=	ft_memcpy.c
SRCS		+=	ft_memmove.c
SRCS		+=	ft_memset.c
SRCS		+=	ft_nblen_base.c
SRCS		+=	ft_nblen.c
SRCS		+=	ft_power.c
SRCS		+=	ft_putaddr_fd.c
SRCS		+=	ft_putaddr.c
SRCS		+=	ft_putchar_fd.c
SRCS		+=	ft_putchar.c
SRCS		+=	ft_putendl_fd.c
SRCS		+=	ft_putendl.c
SRCS		+=	ft_putnbr_fd.c
SRCS		+=	ft_putnbr.c
SRCS		+=	ft_putstr_fd.c
SRCS		+=	ft_putstr.c
SRCS		+=	ft_split.c
SRCS		+=	ft_strcapitalize.c
SRCS		+=	ft_strcasestr.c
SRCS		+=	ft_strcat.c
SRCS		+=	ft_strchr.c
SRCS		+=	ft_strcmp.c
SRCS		+=	ft_strcpy.c
SRCS		+=	ft_strdup.c
SRCS		+=	ft_strisall.c
SRCS		+=	ft_strisalnum.c
SRCS		+=	ft_strisalpha.c
SRCS		+=	ft_strisascii.c
SRCS		+=	ft_strisdigit.c
SRCS		+=	ft_strisprint.c
SRCS		+=	ft_strjoin.c
SRCS		+=	ft_strlcat.c
SRCS		+=	ft_strlcpy.c
SRCS		+=	ft_strlen.c
SRCS		+=	ft_strlowcase.c
SRCS		+=	ft_strmapi.c
SRCS		+=	ft_strncat.c
SRCS		+=	ft_strncmp.c
SRCS		+=	ft_strncpy.c
SRCS		+=	ft_strndup.c
SRCS		+=	ft_strnlen.c
SRCS		+=	ft_strnstr.c
SRCS		+=	ft_strpbrk.c
SRCS		+=	ft_strrchr.c
SRCS		+=	ft_strsplit.c
SRCS		+=	ft_strstr.c
SRCS		+=	ft_strtol.c
SRCS		+=	ft_strtoll.c
SRCS		+=	ft_strtrim.c
SRCS		+=	ft_strupcase.c
SRCS		+=	ft_substr.c
SRCS		+=	ft_tolower.c
SRCS		+=	ft_toupper.c
SRCS		+=	get_next_line.c

## Objects
OBJS		=	$(SRCS:.c=.o)

## Include
INC			=	libft.h

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -Ofast
LIBC		=	ar rc
RM			=	rm -f

.c.o:
			$(MUTE) $(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INC)

$(NAME):	$(OBJS)
			$(MUTE) $(MAKE) -C ft_printf
			$(MUTE) cp ft_printf/libftprintf.a . && mv libftprintf.a $(NAME)
			$(MUTE) $(LIBC) $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(MUTE) $(MAKE) -C ft_printf clean
			$(MUTE) $(RM) $(OBJS)

fclean:		clean
			$(MUTE) $(MAKE) -C ft_printf fclean
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		$(NAME) all clean fclean re
