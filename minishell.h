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

# define SHELL_MSG      "coquillage$>"
# define BUILTIN_COUNT	7

typedef struct	s_lit_status {
		int				quote;
		int				dquote;
		int				backs;
		int				unused_op;
		int				pipe;
		int				redir;
}				t_lit_status;

typedef	int	(*t_binfunc_arr)(char **cmd, t_list **local_env);

typedef struct	s_builtin	{
		char			**builtin_names_arr;
		t_list			*local_env;
		t_binfunc_arr	builtin_func_arr[BUILTIN_COUNT];
}				t_builtin;

typedef struct  s_cmd_data {
    int     			pipefd[2];
    int     			redirfd[2];
    char    			*filename;
    char    			**env_arr;
    char    			**cmd_split;
    int     			builtin_index;
	t_builtin			*builtin_data;
}               t_cmd_data;
int	g_minishell_exit_status;

/*
** PROCESS MNG
*/
int		exec_pipe(char **pipe_split, int index, int piperead_fildes, t_builtin *builtin_data);
void	exec_set_redir(int redirfd[2]);
int		exec_init_cmd_data(t_cmd_data *cmd_data, t_builtin *builtin_data, char *cmd_line);
int		exec_close_cmd_data(t_cmd_data *cmd_data);
int		exec_set_cmd_filename(char *cmd, t_cmd_data *cmd_data);
/*
** REDIRECTIONS
*/
int     redir_input(char **cmd, char *filename);
int     redir_output(char **cmd, char *filename, int append_flag);
int     parse_redirections(char *line, int redirfd[2]);
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
int		is_operator(char c);
char	**shell_split(char const *s, char c);
char	*first_read(char *s);
int		is_lit(char c, t_lit_status *lit_status);
void	lit_status_init(t_lit_status *lit_status);
char	**parse_argv(char *cmd_line);
/*
** ERRORS AND FREE
*/
void    ft_free_strarr(char ***line_split);
/*
** BUILTIN FUNCTIONS
*/
int		builtin_echo(char **cmd, t_list **env);
int		builtin_exit(char **cmd, t_list **env);
int		builtin_pwd(char **argv, t_list **env);
int		builtin_env(char **argv, t_list **env);
int		builtin_cd(char **argv, t_list **env);
int		builtin_export(char **av, t_list **env);
int		builtin_unset(char **av, t_list **env);
char	**builtin_init_names_arr(void);
void	builtin_init_funcarr(t_binfunc_arr *binfunc_arr);
/*
** ENV
*/
char	*env_get_val(t_list *env, char *key);
t_list	*env_get_key(t_list *env, char *key);
void	env_print(t_list *local_env);
t_list	*env_create_list(char **env);

/*
** Create an array of the current env variable.
**
** @param local_env_lst List to take env variable from.
** @return A malloc-ed array ready to be used by execve for exemple.
*/
char	**env_make_arr(t_list *local_env_lst);
/*
** MISC
*/
char	*search_path(char *path, char *bin);
int		close_if(int fd1, int diff);
#endif
