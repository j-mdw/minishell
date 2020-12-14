#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <signal.h>

# include "get_next_line.h"
# include "libft.h"

# define BIN_PATH       "/bin/"
# define BUILT_IN_CMD   1
# define LOCAL_CMD      2
# define SHELL_MSG      "coquillage$>"
# define SHELL_MSG_LEN  12

/*
** PORGRAM CORE
*/
int     exec_builtin(char **arg_split);


/*
** SIGNALS MANAGEMENT
*/
void    set_signals(void);
void    reset_signals(void);
void    sigint_handler(int sig_nb);
void    sigexit_handler(int sig_nb);

/*
** PARSING
*/
int     parse_input(char *line, char ***line_split);

/*
** ERRORS AND FREE
*/
void    free_split(char ***line_split);

#endif
