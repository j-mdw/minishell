NAME	= minishell

SRCS	:= \
main\
get_next_line\
get_next_line_utils


S 		:= src/

O 		:= obj/

I		= inc/

LIBFT	= libft/libft.a

# Clement: I don't believe we need the C_FILES variable
#C_FILES	= \
#$(addprefix $S, $(addsuffix .c, $(SRCS)))


O_FILES	:= \
$(addprefix $O, $(addsuffix .o, $(SRCS)))

#H_FILES	= minishell.h

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I$I

RM		= rm -f
	
all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $^ -o $@ 

# The $O prerequisite below is delcared as an 'order-only' prerequisite
# meaning the rule will be called only if it doesn't exist, and its update
# won't be checked
# Would need to add header files here as well

$O%.o: $S%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft/

clean:
	$(RM) $(O_FILES)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) --directory=libft clean

re: fclean all
	$(MAKE) --directory=libft fclean

.PHONY: all, clean, fclean, re
