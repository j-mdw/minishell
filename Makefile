NAME	= minishell

SRCS	= \
signals_set\
signals_handlers\
\
builtin_echo\
builtin_exit\
builtin_pwd\
builtin_env\
builtin_cd\
builtin_export\
builtin_unset\
builtin_init_names_arr\
builtin_init_funcarr\
builtin_init_data_struct\
builtin_free_data_struct\
\
env_get_val\
env_get_key\
env_print\
env_create_list\
env_make_arr\
\
parse_argv\
parse_first_read\
parse_get_filename\
parse_line\
parse_lit_status_init\
parse_param_trim\
parse_redirections\
parse_shell_split\
\
util_close_if\
util_is_lit\
util_is_operator\
util_part_write\
util_search_path\
\
exec_pipes\
exec_set_redir\
exec_init_cmd_data\
exec_close_cmd_data\
exec_set_cmd_filename\
exec_builtin\
exec_child

SRCS_BONUS	= \
tty_get_line\
tty_cursor\
tty_echo_del\
tty_move_left\
tty_newline\
tty_set_raw_mode\
tty_echo_escape\
tty_write_over\
tty_error\
tty_read_echo\
tty_echo_char\
tty_dynamic_array\
tty_move_cursor\
tty_erase_from_cursor\
tty_iter_hist\
tty_move_word\
tty_get_escape_seq

SRCS_BONUS_FILES = $(addsuffix _bonus, $(SRCS_BONUS))

S 		:= src/

O 		:= obj/

I		= -I .\
		-I libft/

MAIN_O = $Omain.o

MAIN_O_BONUS = $Omain_bonus.o

O_FILES	= $(addprefix $O, $(addsuffix .o, $(SRCS)))

O_BONUS_FILES	= \
$(addprefix $O, $(addsuffix .o, $(SRCS_BONUS_FILES)))

H		= minishell.h\

H_BONUS	= termcaps.h\

LIBFT	= libft/libft.a

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra $I -g3 -O0

RM		= rm -f

ifeq ($(VERSION), standard)

H_TARGET	= $H

TARGET		= $(O_FILES)\
$(MAIN_O)

else

H_TARGET	= $H\
$(H_BONUS)

TARGET		= $(O_FILES)\
$(O_BONUS_FILES)\
$(MAIN_O_BONUS)

endif

all:
	$(MAKE) -C libft/
	make VERSION=standard $(NAME)

bonus:
	$(MAKE) -C libft/
	make VERSION="bonus" $(NAME)

$(NAME): $(TARGET) $(LIBFT)
	$(CC) $^ -o $@

$O%.o: $S%.c $(H_TARGET)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(O_FILES) $(O_BONUS_FILES)
	make --directory=libft clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
