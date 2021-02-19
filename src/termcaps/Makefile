NAME	= termcaps

SRCS	:= \
tty_get_line.c\
tty_cursor.c\
tty_echo_del.c\
tty_move_left.c\
tty_newline.c\
tty_set_raw_mode.c\
tty_escape.c\
tty_write_over.c\
tty_error.c\
tty_read_echo.c\
tty_echo_char.c\
tty_dynamic_array.c\

O_FILES = ${SRCS:c=o}

ROOT_PATH := /home/user42/Documents/minishell/minishell

LIBFT_PATH = $(ROOT_PATH)/libft

LIBFT = $(LIBFT_PATH)/libft.a

TTYLIB = ttylib.a

CC = gcc

CFLAGS = -Werror -Wextra -Werror -g3

all: $(SRCS) $(LIBFT) termcaps.h
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -I$(LIBFT_PATH) -o $(NAME)

# all: $(TTYLIB)

# $(TTYLIB): $(O_FILES)
# 	ar -rcs $@ $^ 

$(O_FILES): termcaps.h
	gcc -c $(SRCS) -I$(LIBFT_PATH) $(LIBFT)

clean:
	rm $(O_FILES)

fclean: clean
	rm $(TTYLIB)

re: fclean all
