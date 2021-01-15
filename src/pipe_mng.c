#include "minishell.h"

int
	*set_pipe(int pipe_fd[2], int stdio_fd_cp[2])
{
	if (pipe(pipe_fd) < 0)
	{
		printf("Error in set_pipe: %s\n", strerror(errno));
		return (NULL);
	}
	if ((stdio_fd_cp[0] = set_fd(STDIN_FILENO, pipe_fd[1])) < 0)
		return (NULL);
	if ((stdio_fd_cp[1] = set_fd(STDOUT_FILENO, pipe_fd[0])) < 0)
		return (NULL);
	return (stdio_fd_cp);
}

int
	close_pipe(int pipe_fd[2], int stdio_fd_cp[2])
{
	int	ret;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if ((ret = reset_fd(stdio_fd_cp[0], STDIN_FILENO)) < 0)
		printf("Error in close_pipe");							// For debug - even if an error occurs here, still want to
																// reset STDOUT before returning
	if ((ret += reset_fd(stdio_fd_cp[1], STDOUT_FILENO)) < 0)	//+= here as reset_fd returns -1 on error, 0 otherwise
		printf("Error in close_pipe");	
	close(stdio_fd_cp[0]);										// close stdin copy
	close(stdio_fd_cp[1]);										// close stdout copy
	return (ret);												// < 0 if an error occured
}