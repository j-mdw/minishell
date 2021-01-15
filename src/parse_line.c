#include "minishell.h"


typedef	struct	s_parse {
		char	**control_op_split;
		char	**pipe_split;
		char	**line_split;
		int		redir_io_saved_fd[2];
		int		redir_file_fd[2];
		int		pipe_fd[2];
		int		pipe_io_saved_fd[2];
}			t_parse;

void
	init_parsing_struct(t_parse	*parse_ptr)
{
	parse_ptr->control_op_split = NULL;
	parse_ptr->pipe_split = NULL;
	parse_ptr->line_split = NULL;
}
 
int
	free_parsing_elem(t_parse *parse_ptr)
{
	if (parse_ptr->control_op_split)
		free_split(&(parse_ptr->control_op_split));
	if (parse_ptr->pipe_split)
		free_split(&(parse_ptr->pipe_split));
	if (parse_ptr->line_split)
		free_split(&(parse_ptr->line_split));
	return (0);
}



int
	parse_input(char *line)
{
	t_parse	parse_data;
	int		i;
	int		j;

	init_parsing_struct(&parse_data);
	if (!(parse_data.control_op_split = ft_split(line, ';')))
		return (-1);
	i = 0;
	while (parse_data.control_op_split[i])
	{
		if (!(parse_data.pipe_split = parse_open_pipe(parse_data.control_op_split[i], parse_data.pipe_fd, parse_data.pipe_io_saved_fd)))
			return (free_parsing_elem(&parse_data) - 1);
		j = 0;
		while (parse_data.pipe_split[j])
		{
			if (parse_set_redirections(parse_data.pipe_split[j], parse_data.redir_io_saved_fd, parse_data.redir_file_fd) < 0)	// Set up redirections
				return (free_parsing_elem(&parse_data) - 1);
			if (!(parse_data.line_split = ft_split(parse_data.pipe_split[j], ' ')))												// Split command
				return (free_parsing_elem(&parse_data) - 1);
			if (exec_builtin(parse_data.line_split) < 0)																		// Execute command
				return (free_parsing_elem(&parse_data) - 1);
			if (reset_redirections(parse_data.redir_io_saved_fd, parse_data.redir_file_fd) < 0)		// ON ERROR, NEED TO MAKE SURE REDIRECTIONS ARE RESET APPROPRIATELY - MAYBE SET STDIN AND STDOUT AT START OF LOOP TO MAKE SURE NO ERRORS ARE POSSIBLE?
				return (free_parsing_elem(&parse_data) - 1);
			free_split(&(parse_data.line_split));
			j++;
		}
		if (parse_data.pipe_fd[0] != -1 && close_pipe(parse_data.pipe_fd, parse_data.pipe_io_saved_fd) < 0) // If a pipe was open, close pipe
			return (free_parsing_elem(&parse_data));
		free_split(&(parse_data.pipe_split));
		i++;
	}
	return (free_parsing_elem(&parse_data));
}
