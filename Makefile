NAME	= minishell

SRCS	:= \
main\
signals\
shell_split\
redirections\
get_filename\
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
\
env_get_val\
env_get_key\
env_print\
env_create_list\
env_make_arr\
\
parse_line\
parse_argv\
search_path\
first_read\
is_lit\
close_if\
\
exec_pipes\
exec_set_redir\
exec_init_cmd_data\
exec_close_cmd_data\
exec_set_cmd_filename\

S 		:= src/

O 		:= obj/

I		= -I .\
		-I libft/

LIBFT	= libft/libft.a

O_FILES	:= \
$(addprefix $O, $(addsuffix .o, $(SRCS)))

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra $I -g3 -O0

RM		= rm -f
	
all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $^ -o $@ 

$O%.o: $S%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft/

bonus: all

clean:
	$(RM) $(O_FILES)
	make --directory=libft clean

fclean: clean
	$(RM) $(NAME)
	make --directory=libft fclean

re: fclean all

.PHONY: all, bonus, clean, fclean, re
