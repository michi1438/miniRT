# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 10:21:23 by mguerga           #+#    #+#              #
#    Updated: 2023/10/18 11:39:36 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

NAME = minirt.out

CC = gcc

CFLAGS = -Werror -Wall -Wextra

SRC_MINIRT = rt_main.c

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
