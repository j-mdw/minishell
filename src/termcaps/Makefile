NAME	= termcaps

SRCS	:= \
termcaps.c\
tty_cursor.c\
tty_echo_del.c\
tty_move_left.c\
tty_newline.c\
tty_set_raw_mode.c\
tty_escape.c\
tty_write_over.c

ROOT_PATH := /home/user42/Documents/minishell

LIBFT_PATH = $(ROOT_PATH)/libft

LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc

CFLAGS = -Werror -Wextra -Werror

all: $(SRCS) $(LIBFT) termcaps.h
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -I$(LIBFT_PATH) -o $(NAME)

clean:
	rm $(NAME)

fclean: clean
	rm $(NAME)

re: fclean all