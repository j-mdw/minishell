#include "minishell.h"

int
	parsing_reset_close_fds(t_parse *parse_ptr)
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