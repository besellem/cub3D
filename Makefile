# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 20:27:25 by besellem          #+#    #+#              #
#    Updated: 2021/02/05 01:18:40 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Constants
MUTE		=	@
NAME		=	cub3D
SRCS_PATH	=	./srcs
BMP_FILE	=	./saved.bmp

## Sources
INCS		=	incs libft/libft.a
MLIBX		=	libmlx.dylib

SRCS		+=	main.c
SRCS		+=	$(SRCS_PATH)/common.c
SRCS		+=	$(SRCS_PATH)/common2.c
SRCS		+=	$(SRCS_PATH)/common3.c
SRCS		+=	$(SRCS_PATH)/common4.c
SRCS		+=	$(SRCS_PATH)/common5.c
SRCS		+=	$(SRCS_PATH)/config_checker.c
SRCS		+=	$(SRCS_PATH)/display.c
SRCS		+=	$(SRCS_PATH)/events.c
SRCS		+=	$(SRCS_PATH)/gun.c
SRCS		+=	$(SRCS_PATH)/handle_bonus.c
SRCS		+=	$(SRCS_PATH)/handle_keys.c
SRCS		+=	$(SRCS_PATH)/init.c
SRCS		+=	$(SRCS_PATH)/map_checker.c
SRCS		+=	$(SRCS_PATH)/map_parser.c
SRCS		+=	$(SRCS_PATH)/map_validator.c
SRCS		+=	$(SRCS_PATH)/minimap.c
SRCS		+=	$(SRCS_PATH)/parser.c
SRCS		+=	$(SRCS_PATH)/raycasting.c
SRCS		+=	$(SRCS_PATH)/raycasting_utils.c
SRCS		+=	$(SRCS_PATH)/save.c
SRCS		+=	$(SRCS_PATH)/sound_and_music.c
SRCS		+=	$(SRCS_PATH)/sprites.c
SRCS		+=	$(SRCS_PATH)/utils.c

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
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
			$(MUTE) $(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit -I $(INCS)
endif

ifeq ($(UNAME), Linux)
$(NAME):
			$(MUTE) echo "\033[31;1mCompiling for Linux...\033[0m"
			$(MUTE) $(MAKE) -C libft all
			$(MUTE) $(MAKE) -C mlx_linux all
			$(MUTE) # -D BONUS -> TO ENABLE BONUSES (to add)
			$(MUTE) $(CC) $(CFLAGS) -Ofast -I/usr/include -Imlx_linux $(SRCS) -Imlx_linux -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -I $(INCS) -o $(NAME)
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
