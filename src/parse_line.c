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
	parse_ptr->redir_file_fd[0] = STDIN_FILENO;
	parse_ptr->redir_file_fd[1] = STDOUT_FILENO;


}

int
	free_parsing_reset_fd(t_parse *parse_ptr)
{
	int	ret;

	ret = 0;
	if (parse_ptr->control_op_split)
		free_split(&(parse_ptr->control_op_split));
	if (parse_ptr->pipe_split)
		free_split(&(parse_ptr->pipe_split));
	if (parse_ptr->cmd_split)
		free_split(&(parse_ptr->cmd_split));
	if (parse_ptr->pipe_io_saved_fd[0] != STDIN_FILENO)
		ret += reset_fd(parse_ptr->pipe_io_saved_fd[0], STDIN_FILENO);
	if (parse_ptr->pipe_io_saved_fd[1] != STDOUT_FILENO)
		ret += reset_fd(parse_ptr->pipe_io_saved_fd[1], STDOUT_FILENO);
	if (parse_ptr->pipe_fd[0] >= 0)
		close(parse_ptr->pipe_fd[0]);
	if (parse_ptr->pipe_fd[1] >= 0)
		close(parse_ptr->pipe_fd[1]);
	/* if (parse_ptr->redir_file_fd[0] != STDIN_FILENO || \
	 parse_ptr->redir_file_fd[1] != STDOUT_FILENO)
	 	ret += reset_redirections(parse_ptr->redir_io_saved_fd, parse_ptr->redir_file_fd);
	 if (parse_ptr->pipe_fd[0] != -1)
	 	ret += close_pipe(parse_ptr->pipe_fd, parse_ptr->pipe_io_saved_fd);
	*/
	return (ret);
}

int
	parse_pipe(t_parse *p_ptr)
{
	int	i;
	
	i = 0;
	p_ptr->pipe_io_saved_fd[0] = dup(STDIN_FILENO);			// Save copy of stdin
	p_ptr->pipe_io_saved_fd[1] = dup(STDOUT_FILENO);		// Save copy of stdout
	while (p_ptr->pipe_split[i])
	{
		if (p_ptr->pipe_split[i + 1])
		{
			if (pipe(p_ptr->pipe_fd) < 0)
				return (-1);
			if (dup2(p_ptr->pipe_fd[1], STDOUT_FILENO) < 0)			// Set stdout to pipi[1]
				return (free_parsing_reset_fd(p_ptr) - 1);
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
		exec_builtin(p_ptr->cmd_split);
		free_split(&(p_ptr->cmd_split));	
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

int
	parse_input(char *line)
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
			return (free_parsing_reset_fd(&parse_data) - 1);
		// printf("Pipe split: %s\n", parse_data.pipe_split[0]);
		if (parse_pipe(&parse_data) < 0)
			return (free_parsing_reset_fd(&parse_data) - 1);
		free_split(&(parse_data.pipe_split));
		i++;
	}
	return (free_parsing_reset_fd(&parse_data));
}
/*
















		if (!(parse_data.pipe_split = parse_open_pipe(parse_data.control_op_split[i], parse_data.pipe_fd, parse_data.pipe_io_saved_fd)))
			return (free_parsing_reset_fd(&parse_data) - 1);
		j = 0;
		dprintf(parse_data.pipe_io_saved_fd[1],"pipe_io_saved_fd: |%d|%d|\n", parse_data.pipe_io_saved_fd[0], parse_data.pipe_io_saved_fd[1]);
		dprintf(parse_data.pipe_io_saved_fd[1], "Pipe split: |%s|%s|\n", parse_data.pipe_split[0], parse_data.pipe_split[1]);
		while (parse_data.pipe_split[j])
		{
			//if (parse_set_redirections(parse_data.pipe_split[j], parse_data.redir_io_saved_fd, parse_data.redir_file_fd) < 0)	// Set up redirections
				// return (free_parsing_reset_fd(&parse_data) - 1);
			if (!(parse_data.cmd_split = ft_split(parse_data.pipe_split[j], ' ')))												// Split command
				return (free_parsing_reset_fd(&parse_data) - 1);
			dprintf(parse_data.pipe_io_saved_fd[1], "Cmd split: |%s|%s|\n", parse_data.cmd_split[0], parse_data.cmd_split[1]);
			if (exec_builtin(parse_data.cmd_split) < 0)																		// Execute command
				return (free_parsing_reset_fd(&parse_data) - 1);
			if (i == 0)
			{
				close(parse_data.pipe_fd[1]);
				reset_fd(parse_data.pipe_io_saved_fd[1], STDOUT_FILENO);
			}
			if (i == 1)
			{
				close(parse_data.pipe_fd[0]);
				reset_fd(parse_data.pipe_io_saved_fd[0], STDIN_FILENO);
			}
			// print_file(parse_data.pipe_fd[0], parse_data.pipe_io_saved_fd[1]);
			// if (reset_redirections(parse_data.redir_io_saved_fd, parse_data.redir_file_fd) < 0)
				// return (free_parsing_reset_fd(&parse_data) - 1);
			dprintf(parse_data.pipe_io_saved_fd[1], "Zozo1: |%s|%s|\n", parse_data.cmd_split[0], parse_data.cmd_split[1]);
			free_split(&(parse_data.cmd_split));

			dprintf(parse_data.pipe_io_saved_fd[1], "Zozo2\n");
			j++;
		}
		// if (parse_data.pipe_fd[1] != -1 && print_file(parse_data.pipe_fd[0], parse_data.pipe_io_saved_fd[1]) < 0)
		// 		return(free_parsing_reset_fd(&parse_data) - 1);
		// if (parse_data.pipe_fd[0] != -1 && close_pipe(parse_data.pipe_fd, parse_data.pipe_io_saved_fd) < 0) // If a pipe was open, close pipe
		// 	return (free_parsing_reset_fd(&parse_data) - 1);
		free_split(&(parse_data.pipe_split));
		i++;
	}
	return (free_parsing_reset_fd(&parse_data));
}
*/