# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/14 05:11:51 by jmaydew           #+#    #+#              #
#    Updated: 2021/01/04 14:48:59 by jmaydew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
CC = gcc
SRC_FILES = ft_itoa.c ft_putnbr_fd.c ft_strmapi.c ft_atoi.c ft_memccpy.c \
ft_putstr_fd.c ft_strncmp.c ft_bzero.c ft_memchr.c ft_split.c ft_strnstr.c \
ft_calloc.c ft_memcmp.c ft_strchr.c ft_strrchr.c ft_isalnum.c ft_memcpy.c \
ft_strdup.c ft_strtrim.c ft_isalpha.c ft_memmove.c ft_strjoin.c ft_substr.c \
ft_isascii.c ft_memset.c ft_strlcat.c ft_tolower.c ft_isdigit.c \
ft_putchar_fd.c ft_strlcpy.c ft_toupper.c ft_isprint.c ft_putendl_fd.c \
ft_strlen.c
OBJ_FILES := ${SRC_FILES:c=o}

I = ../inc

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) -I$I -c $(SRC_FILES)

bonus: all

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f libft.a

re: fclean all

.PHONY: all bonus clean fclean re
