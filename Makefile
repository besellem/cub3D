# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2021/03/08 09:00:49 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Constants
MUTE		=	@
NAME		=	cub3D
BMP_FILE	=	./saved.bmp

## Sources
INCS		=	-I incs -Llibft -lft -Ilibft/incs
MLIBX		=	libmlx.dylib

# Paths
PATH_SRCS	:=	./srcs

PATH_OTHERS	:=	__others__
PATH_BONUS	:=	bonus
PATH_COMMON	:=	common
PATH_ENGINE	:=	engine
PATH_EVENTS	:=	events
PATH_PARSER	:=	parser

SRCS		=	$(PATH_SRCS)/main.c \
				$(PATH_SRCS)/$(PATH_OTHERS)/save.c \
				$(PATH_SRCS)/$(PATH_OTHERS)/utils.c \
				$(PATH_SRCS)/$(PATH_BONUS)/gun.c \
				$(PATH_SRCS)/$(PATH_BONUS)/init_bonus.c \
				$(PATH_SRCS)/$(PATH_BONUS)/minimap.c \
				$(PATH_SRCS)/$(PATH_BONUS)/sound_and_music.c \
				$(PATH_SRCS)/$(PATH_COMMON)/angles.c \
				$(PATH_SRCS)/$(PATH_COMMON)/checkers.c \
				$(PATH_SRCS)/$(PATH_COMMON)/common.c \
				$(PATH_SRCS)/$(PATH_COMMON)/free_cub.c \
				$(PATH_SRCS)/$(PATH_COMMON)/math_utils.c \
				$(PATH_SRCS)/$(PATH_COMMON)/rgb.c \
				$(PATH_SRCS)/$(PATH_ENGINE)/display.c \
				$(PATH_SRCS)/$(PATH_ENGINE)/engine_loop.c \
				$(PATH_SRCS)/$(PATH_ENGINE)/raycasting_utils.c \
				$(PATH_SRCS)/$(PATH_ENGINE)/raycasting.c \
				$(PATH_SRCS)/$(PATH_ENGINE)/sprites.c \
				$(PATH_SRCS)/$(PATH_EVENTS)/handle_keys.c \
				$(PATH_SRCS)/$(PATH_EVENTS)/quit_events.c \
				$(PATH_SRCS)/$(PATH_PARSER)/config_checker.c \
				$(PATH_SRCS)/$(PATH_PARSER)/init_cub.c \
				$(PATH_SRCS)/$(PATH_PARSER)/map_checker.c \
				$(PATH_SRCS)/$(PATH_PARSER)/map_parser.c \
				$(PATH_SRCS)/$(PATH_PARSER)/map_validator.c \
				$(PATH_SRCS)/$(PATH_PARSER)/parser.c

OBJS		=	$(SRCS:.c=.o)

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3 -Ofast -fsanitize=address
RM			=	rm -f
RMRF		=	rm -rf

# Get system name
UNAME		:=	$(shell uname)


## Targets
# Check the system -- macOS or Linux -- for compilation
ifeq ($(UNAME), Darwin)
$(NAME):
			$(MUTE) echo "\033[31;1mCompiling for macOS...\033[0m"
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx all
			$(MUTE) cp ./mlx/$(MLIBX) .
			$(MUTE) # -D BONUS -> TO ENABLE BONUSES (to add)
			$(MUTE) $(CC) $(CFLAGS) -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit $(INCS)
endif


ifeq ($(UNAME), Linux)
$(NAME):
			$(MUTE) echo "\033[31;1mCompiling for Linux...\033[0m"
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx_linux all
			$(MUTE) # -D BONUS -> TO ENABLE BONUSES (to add)
			$(MUTE) $(CC) $(CFLAGS) -I/usr/include -Imlx_linux $(SRCS) -Imlx_linux -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm $(INCS) -o $(NAME)
endif


all:		$(NAME)


bonus:		all


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


.PHONY:		$(NAME) all bonus clean fclean re
