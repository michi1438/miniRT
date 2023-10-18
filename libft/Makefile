# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 20:18:13 by mguerga           #+#    #+#              #
#    Updated: 2023/04/19 15:41:48 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

SRC_MAIN = ft_bzero.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRC_GNL = get_next_line_utils_bonus.c get_next_line_bonus.c

SRC_PRINTF = optionctrl.c optionctrl_supl.c print_toconv.c print_toconv_supl.c \
			 print_toconv_supll.c print_toconv_suplll.c print_toconv_supllll.c \
			 printfer.c printfer_supl.c printparser.c printparser_supl.c

SOURCES = $(addprefix ft_main/, $(SRC_MAIN)) \
			$(addprefix ft_gnl/, $(SRC_GNL)) \
			$(addprefix ft_printf/, $(SRC_PRINTF)) \


OBJS = $(SOURCES:c=o)
	
CC = gcc

AR = ar rc

CFLAGS = -Werror -Wall -Wextra

all: $(NAME) 

$(NAME): $(OBJS) 
	$(AR) $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus 
