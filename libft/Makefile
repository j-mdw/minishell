# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 19:53:29 by clkuznie          #+#    #+#              #
#    Updated: 2021/02/25 16:19:37 by clkuznie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

LIBC			:= \
ft_atoi.c					ft_memchr.c					ft_strjoin.c\
ft_bzero.c					ft_memcmp.c					ft_strlcat.c\
ft_calloc.c					ft_memcpy.c					ft_strlcpy.c\
ft_isalnum.c				ft_memmove.c				ft_strlen.c\
ft_isalpha.c				ft_memset.c					ft_strmapi.c\
ft_isascii.c				ft_nbrlen.c					ft_strncmp.c\
ft_isdigit.c				ft_putchar_fd.c				ft_strndup.c\
ft_isinflow.c				ft_putendl_fd.c				ft_strnstr.c\
ft_isinset.c				ft_putnbr_fd.c				ft_strrchr.c\
ft_isprint.c				ft_putstr_fd.c				ft_strtrim.c\
ft_iswspace.c				ft_split.c					ft_substr.c\
ft_itoa.c					ft_strchr.c					ft_tolower.c\
ft_memccpy.c				ft_strdup.c					ft_toupper.c

LST				:= \
ft_lstadd_back.c\
ft_lstadd_front.c\
ft_lstclear.c\
ft_lstdelone.c\
ft_lstiter.c\
ft_lstlast.c\
ft_lstmap.c\
ft_lstnew.c\
ft_lstsize.c

PRINTF			:= \
ft_printf_bonus.c\
print_handler.c\
handler_bonus.c\
get_options.c\
utils.c

GNL				:= \
get_next_line.c

NEW_UTILS		:= \
power_base_to2.c\
ft_strtod.c

JANUARY_2021	:= \
ft_strcmp.c\
ft_strcpy.c\
ft_strfind.c\
ft_putstrarr.c\
ft_free_strnarr.c\
ft_list_remove_if.c\
ft_free_strarr.c\
ft_isblank.c

FILES			:= \
$(addprefix libc/, $(LIBC))\
$(addprefix printf/, $(PRINTF))\
$(addprefix lst/, $(LST))\
$(addprefix gnl/, $(GNL))\
$(addprefix new_utils/, $(NEW_UTILS))\
$(addprefix january_2021/, $(JANUARY_2021))

OBJS			= $(FILES:%.c=%.o)

CC				= gcc
CFLAGS			= -c -Wall -Wextra -Werror

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o:			%.c libft.h
	$(CC) $(CFLAGS) -I . $< -o $@

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean:			clean
	$(RM) $(NAME)

re:				fclean all
