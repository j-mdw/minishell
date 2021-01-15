#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>

# include "get_next_line.h"
# include "libft.h"

# define BIN_PATH       "/bin/"
# define BUILT_IN_CMD   1
# define LOCAL_CMD      2
# define SHELL_MSG      "coquillage$>"

/*
** PORGRAM CORE
*/
int     exec_builtin(char **arg_split);

/*
** REDIRECTIONS
*/
int     redir_input(char **cmd, char *filename);
int     redir_output(char **cmd, char *filename, int append_flag);
int     parse_set_redirections(char *line, int redir_io_saved_fd[2], int redir_file_fd[2]);
int     reset_redirections(int redir_io_saved_fd[2], int redir_file_fd[2]);
int     reset_fd(int save_fd, int reset_fd);
int     set_fd(int start_fd, int set_fd);

/*
** PIPES
*/

char    **parse_open_pipe(char *line, int pipe_fd[2], int pipe_io_saved_fd[2]);
int     close_pipe(int pipe_fd[2], int stdio_fd_cp[2]);
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
int     parse_input(char *line);
char    *get_filename(char *line);
int     ft_isblank(int c);
/*
** ERRORS AND FREE
*/
void    free_split(char ***line_split);

#endif
