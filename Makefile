NAME	= minishell

SRCS	:= \
main

S 		:= src/

O 		:= obj/

# Clement: I don't believe we need the C_FILES variable
#C_FILES	= \
#$(addprefix $S, $(addsuffix .c, $(SRCS)))


O_FILES	:= \
$(addprefix $O, $(addsuffix .o, $(SRCS)))

#H_FILES	= minishell.h

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address

RM		= rm -rf
	
all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $< -o $@ 

$O:
	@mkdir -p $@

# The $O prerequisite below is delcared as an 'order-only' prerequisite
# meaning the rule will be called only if it doesn't exist, and its update
# won't be checked

# Would need to add header files here as well

$O%.o: $S%.c | $O
	$(CC) -c $< -o $@

clean:
	$(RM) $O

fclean: clean

re: fclean all

.PHONY: all, clean, fclean, re
