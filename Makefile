NAME	= minishell

SRCS	:= \
main\
get_next_line\
get_next_line_utils\
signals\
parse_line\
free_split\
exec_function\
redirections\
pipe_mng\
get_filename\
set_fd\
reset_fd\
echo\

S 		:= src/

O 		:= obj/

I		= inc/

LIBFT	= libft/libft.a

O_FILES	:= \
$(addprefix $O, $(addsuffix .o, $(SRCS)))

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I$I -g

RM		= rm -f
	
all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $^ -o $@ 

$O%.o: $S%.c
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
