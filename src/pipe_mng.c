#include "minishell.h"

/*
** Open a pipe
** Save read end of pipe in pipe_fd[0]
** Save write end of pipe in pipe_fd[1]
** Save previous STDIN & STDOUT fds in stdio_fd_cp
*/

int
	set_pipe(int pipe_fd[2], int stdio_fd_cp[2])
{
	if (pipe(pipe_fd) < 0)                                          // Create pipe, set pipe_fd[0] to read end of the pipe, and pipe_fd[1] to write end
		return (-1);
	if ((stdio_fd_cp[0] = set_fd(STDIN_FILENO, pipe_fd[0])) < 0)    // Set stdin to read end of the pipe
		return (-1);
	if ((stdio_fd_cp[1] = set_fd(STDOUT_FILENO, pipe_fd[1])) < 0)   // Set stdout to write end of the pipe
		return (-1);
	return (0);
}

/*
** Closes pipe_fd's
** Set STDIN to stdio_fd_cp[0]
** Set STDOUT to stdio_fd_cp[1]
** Close STDIN and STDOUT copies
*/

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

/*
** Split line on '|'
** Open a pipe and set stdin/stdout accordingly
** If no pipe in 'line', stdin/stdout remain unchanged and pipe_fd[0 and 1] are set to -1
*/

char
    **parse_open_pipe(char *line, int pipe_fd[2], int pipe_io_saved_fd[2])
{
    char    **pipe_split;

    pipe_fd[0] = -1;                                    // Default value - if still -1 at end of function, means there's no pipe
    pipe_fd[1] = -1;
	if (!(pipe_split = ft_split(line, '|')))	        // Error if ft_split returns NULL
			return (NULL);
    if (pipe_split[1] != NULL)					        // If 2nd element of pipe_split is NULL, there is no pipe
    {
        if (set_pipe(pipe_fd, pipe_io_saved_fd) < 0)	// Set up pipe, with write fd in pipe_fd[0] and read fd in pipe_fd[1]
            return (NULL);
    }
    return (pipe_split);    
}