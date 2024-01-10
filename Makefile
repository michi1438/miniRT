# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 10:21:23 by mguerga           #+#    #+#              #
#    Updated: 2024/01/08 12:13:51 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

NAME = minirt.out

CC = gcc

CFLAGS = -Werror -Wall -Wextra# -O3 #-g3 -fsanitize=leak

SRC_MINIRT = rt_main.c rt_err_handling.c rt_scene_parsing.c rt_display.c \
			 rt_fill_shapes.c rt_fill_lightsncamera.c rt_utils.c rt_testin.c \
			 rt_scene.c rt_vecmath.c rt_intersect.c rt_matrices.c \
			 rt_fetch_elem.c rt_fill_control.c

SRC_UTIL = util1.c util2.c util3.c util4.c util5.c camera.c camera2.c camera3.c util6.c item.c util7.c\
			util8.c util9.c util10.c draw_line.c util11.c util12.c util13.c util14.c util15.c util16.c\
			util17.c

SOURCES_UTIL = $(addprefix src/util/, $(SRC_UTIL))

SOURCES_ = $(addprefix src/, $(SRC_MINIRT))

SOURCES = $(SOURCES_UTIL) $(SOURCES_)

INCLUDES = src/rt_head.h

OBJS = $(SOURCES:c=o)

OTHERLIBS = -Llibft/ -lft -lm

ifeq ($(OS), Darwin)
MINILIBX = -Lminilibx_opengl_20191021/ -lmlx -framework OpenGL -framework Appkit
endif

ifeq ($(OS), Linux)
MINILIBX = -Lminilibx-linux/ -lmlx -lX11 -lXext
endif

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	make -C libft/
	make -C minilibx-linux/
	$(CC) -I$(INCLUDES) $(CFLAGS) $(OBJS) $(MINILIBX) $(OTHERLIBS) -o $(NAME)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: clean fclean re bonus 
