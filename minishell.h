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
# define MAND_CMD	{"echo", "exit"}


typedef	struct	s_parse {
		char	**control_op_split;
		char	**pipe_split;
		char	**cmd_split;
		char	**env;
		int		redir_io_saved_fd[2];
		int		redir_file_fd[2];
		int		pipe_fd[2];
		int		pipe_io_saved_fd[2];
}			    t_parse;

/*
** PORGRAM CORE
*/
int     exec_function(char **cmd, char **env);
/*
** REDIRECTIONS
*/
int     redir_input(char **cmd, char *filename);
int     redir_output(char **cmd, char *filename, int append_flag);
int     parse_set_redirections(char *line, int redir_io_saved_fd[2]);
int     reset_redirections(int redir_io_saved_fd[2]);
int     reset_fd(int save_fd, int reset_fd);
int     set_fd(int oldfd, int newfd);
/*
** PIPES
*/
char    **parse_open_pipe(char *line, int pipe_fd[2], int pipe_io_saved_fd[2]);
int     set_pipe(int pipe_fd[2], int stdio_fd_cp[2]);
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
int     parse_input(char *line, char **env);
char    *get_filename(char *line);
int     ft_isblank(int c);
/*
** ERRORS AND FREE
*/
void    free_split(char ***line_split);
int     free_parsing(t_parse *parse_ptr);
int		reset_close_fds(t_parse *parse_ptr);

/*
** MANDOTARY FUNCTIONS
*/
int		echo(char **cmd);

/*
** MISC
*/

#endif