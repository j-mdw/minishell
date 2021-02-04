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

# include "libft.h"

# define BIN_PATH       "/bin/"
# define BUILT_IN_CMD   1
# define LOCAL_CMD      2
# define SHELL_MSG      "coquillage$>"
# define BUILTIN_COUNT	6

typedef	struct	s_parse {
		char			**control_op_split;
		char			**pipe_split;
		char			**cmd_split;
		int				redir_io_saved_fd[2];
		int				redir_file_fd[2];
		int				pipe_fd[2];
		int				pipe_io_saved_fd[2];
}			    t_parse;

typedef	int	(*t_binfunc_arr)(char **cmd, t_list **local_env);

typedef struct	s_builtin	{
		char			**builtin_names_arr;
		t_binfunc_arr	buitin_func_arr[BUILTIN_COUNT];
		t_list			*local_env;
}				t_builtin;


/*
** PROCESS MNG
*/
int		exec_function(char **cmd, t_builtin *builtin_data);
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
** SIGNALS MNG
*/
void    set_signals(void);
void    reset_signals(void);
void    sigint_handler(int sig_nb);
void    sigexit_handler(int sig_nb);
/*
** PARSING
*/
int		parse_input(char *line, t_builtin *builtin_data);
char    *get_filename(char *line);
int     ft_isblank(int c);
/*
** ERRORS AND FREE
*/
void    free_strarr(char ***line_split);
int     free_parsing(t_parse *parse_ptr);
int		reset_close_fds(t_parse *parse_ptr);
/*
** BUILTIN FUNCTIONS
*/
int		builtin_echo(char **cmd, t_list **env);
int		builtin_exit(char **cmd, t_list **env);
int		builtin_pwd(char **argv, t_list **env);
int		builtin_env(char **argv, t_list **env);
int		builtin_cd(char **argv, t_list **env);
int		builtin_export(char **av, t_list **env);
char	**builtin_init_names_arr(void);
void	builtin_init_funcarr(t_binfunc_arr *binfunc_arr);
/*
** ENV
*/
char	*env_get_val(t_list *env, char *key);
void	env_print(t_list *local_env);
t_list	*env_create_list(char **env);

/*
** Create an array of the current env variable.
**
** @param local_env_lst List to take env variable from.
** @return A malloc-ed array ready to be used by execve for exemple.
*/
char	**env_make_arr(t_list *local_env_lst);

#endif
