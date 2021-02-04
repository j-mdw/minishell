#include "minishell.h"

void
	init_parsing_struct(t_parse	*parse_ptr)
{
	parse_ptr->control_op_split = NULL;
	parse_ptr->pipe_split = NULL;
	parse_ptr->cmd_split = NULL;
	parse_ptr->pipe_fd[0] = -1;
	parse_ptr->pipe_fd[1] = -1;
	parse_ptr->pipe_io_saved_fd[0] = STDIN_FILENO;
	parse_ptr->pipe_io_saved_fd[1] = STDOUT_FILENO;
	parse_ptr->redir_io_saved_fd[0] = STDIN_FILENO;
	parse_ptr->redir_io_saved_fd[1] = STDOUT_FILENO;
}

int
	reset_close_fds(t_parse *parse_ptr)
{
	int	ret;

	ret = 0;
	if (parse_ptr->pipe_io_saved_fd[0] != STDIN_FILENO)
		ret += reset_fd(parse_ptr->pipe_io_saved_fd[0], STDIN_FILENO);
	if (parse_ptr->pipe_io_saved_fd[1] != STDOUT_FILENO)
		ret += reset_fd(parse_ptr->pipe_io_saved_fd[1], STDOUT_FILENO);
	if (parse_ptr->pipe_fd[0] >= 0)
		close(parse_ptr->pipe_fd[0]);
	if (parse_ptr->pipe_fd[1] >= 0)
		close(parse_ptr->pipe_fd[1]);
	if (parse_ptr->redir_io_saved_fd[0] != STDIN_FILENO || \
	 parse_ptr->redir_io_saved_fd[1] != STDOUT_FILENO)
	 	ret += reset_redirections(parse_ptr->redir_io_saved_fd);
	return (ret);
}

/*
** Free t_parse arrays if memory was allocated
** return 0
*/

int
	free_parsing(t_parse *parse_ptr)
{
	if (parse_ptr->control_op_split)
		free_strarr(&(parse_ptr->control_op_split));
	if (parse_ptr->pipe_split)
		free_strarr(&(parse_ptr->pipe_split));
	if (parse_ptr->cmd_split)
		free_strarr(&(parse_ptr->cmd_split));
	return (0);
}

int
	parse_pipe(t_parse *p_ptr, t_builtin *builtin_data)
{
	int	i;
	int	exitstatus;

	i = 0;
	p_ptr->pipe_io_saved_fd[0] = dup(STDIN_FILENO);				// Save copy of stdin
	p_ptr->pipe_io_saved_fd[1] = dup(STDOUT_FILENO);			// Save copy of stdout
	while (p_ptr->pipe_split[i])
	{
		if (p_ptr->pipe_split[i + 1])
		{
			if (pipe(p_ptr->pipe_fd) < 0)
				return (-1);
			if (dup2(p_ptr->pipe_fd[1], STDOUT_FILENO) < 0)		// Set stdout to pipi[1]
				return (- 1);
			close(p_ptr->pipe_fd[1]); 							// close pipe_fd[1] - copy saved in fd=1
			p_ptr->pipe_fd[1] = -1;
		}
		else
		{
			if (reset_fd(p_ptr->pipe_io_saved_fd[1], STDOUT_FILENO) < 0)	// If last command, reset stdout
				return (-1);
			p_ptr->pipe_io_saved_fd[1] = STDOUT_FILENO;
		}
		if (parse_set_redirections(p_ptr->pipe_split[i], p_ptr->redir_io_saved_fd) < 0)	// Set up redirections
			return (-1);
		if (!(p_ptr->cmd_split = ft_split(p_ptr->pipe_split[i], ' ')))
			return (-1);
		if ((exitstatus = exec_function(p_ptr->cmd_split, builtin_data)) < 0)
		{
			// printf("Exit status: %d | errno: %d\n", exitstatus, errno);
			// printf("Error: %s | %s\n", strerror(errno), strerror(exitstatus));
			return (-1);
		}
		free_strarr(&(p_ptr->cmd_split));	
		if (reset_redirections(p_ptr->redir_io_saved_fd) < 0)
			return (-1);
		dup2(p_ptr->pipe_fd[0], STDIN_FILENO); 				// Set stdin to pipe[0]
		close(p_ptr->pipe_fd[0]); 							// Close initial pipe[0] fd as a duplicate is now in fd=0
		p_ptr->pipe_fd[0] = -1;
		i++;
	}			
	if (reset_fd(p_ptr->pipe_io_saved_fd[0], STDIN_FILENO) < 0)
		return (-1);
	p_ptr->pipe_io_saved_fd[0] = STDIN_FILENO;
	return (0);
}
/*
** Split line on ';' then on '|'
** Sends the splited output to 'parse_pipe'
** Returns -1 on program error or Exit Status of 
** Returns 0 on success, -1 on error
*/

int
	parse_input(char *line, t_builtin *builtin_data)
{
	t_parse	parse_data;
	int		i;

	init_parsing_struct(&parse_data);
	if (!(parse_data.control_op_split = ft_split(line, ';')))
		return (-1);
	i = 0;
	while (parse_data.control_op_split[i])
	{
		if (!(parse_data.pipe_split = ft_split(parse_data.control_op_split[i], '|')))
			return (free_parsing(&parse_data) - 1);
		if (parse_pipe(&parse_data, builtin_data) < 0)
			return (free_parsing(&parse_data) + reset_close_fds(&parse_data) - 1);
		free_strarr(&(parse_data.pipe_split));
		i++;
	}
	return (free_parsing(&parse_data));
}