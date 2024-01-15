# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 10:21:23 by mguerga           #+#    #+#              #
#    Updated: 2024/01/15 13:03:49 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

NAME = minirt.out

CC = gcc

CFLAGS = -Werror -Wall -Wextra# -O3 #-g3 -fsanitize=leak

SRC_MINIRT = rt_main.c rt_err_handling.c rt_scene_parsing.c rt_display.c \
			 rt_fill_shapes2.c rt_fill_shapes.c rt_fill_lightsncamera.c rt_utils.c rt_testin.c \
			 rt_scene.c rt_vecmath.c rt_intersect.c rt_matrices.c \
			 rt_fetch_elem.c rt_fill_control.c

SOURCES = $(addprefix src/, $(SRC_MINIRT))

OBJS = $(SOURCES:c=o)

OTHERLIBS = -Llibft/ -lft -lm

ifeq ($(OS), Darwin)
MINILIBX = -Lminilibx_opengl_20191021/ -lmlx -framework OpenGL -framework Appkit
endif

ifeq ($(OS), Linux)
MINILIBX = -Lminilibx-linux/ -lmlx -lX11 -lXext
endif

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX) $(OTHERLIBS) -o $(NAME)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: clean fclean re bonus 
