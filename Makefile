NAME	= minishell

SRCS	:= \
main\
get_next_line\
get_next_line_utils\
signals\
parse_line\
free_split\
exec_builtin\


S 		:= src/

O 		:= obj/

I		= inc/

LIBFT	= libft/libft.a

O_FILES	:= \
$(addprefix $O, $(addsuffix .o, $(SRCS)))

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I$I

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

fclean: clean
	$(RM) $(NAME)
	$(MAKE) --directory=libft clean

re: fclean all
	$(MAKE) --directory=libft fclean

.PHONY: all, bonus, clean, fclean, re
