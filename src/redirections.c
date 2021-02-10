#include "minishell.h"


/*
** Open and create a file if necessary, in TRUNC or append mode
** depending on '>' vs '>>'
** returns the fd of the file opened
** overwrites the filename and redir symbols with whitespaces
*/

static int
    parse_output_redir(char *line)
{
    int     i;
    int     append_flag;
    int     fd;
    char    *filename;

    i = 0;
    line[i] = ' ';			// Overwritting redirection symbol
    i++;
    append_flag = O_TRUNC;
    if (line[i] == '>')
    {
        append_flag = O_APPEND;
        line[i] = ' ';
        i++;
    }														
    if (!(filename = get_filename(&(line[i]))))	// Parsing of get_filename not final yet
        return (-1);
    if ((fd = open(filename, O_RDWR | O_CREAT | append_flag, 0664)) < 0)
        return (-1);   // Open filename, if it doesn't exist, create it
    while (ft_isblank(line[i]))
        i++;
    ft_memset(&(line[i]), ' ', ft_strlen(filename));		// overwritting filename with ' ' in line
    free(filename);
    return (fd);
}

/*
** Find filename and Open the correcponding file if it exists
** returns the fd of the file opened or -1 if it doesn't exist
** overwrites the filename and redir symbols with whitespaces
*/

static int
    parse_input_redir(char *line)
{
    int     i;
    int     fd;
    char    *filename;

    i = 0;
    line[i] = ' ';			                            // Overwritting redirection symbol
    i++;														
    if (!(filename = get_filename(&(line[i]))))	        // Parsing of get_filename not final yet
        return (-1);
    if ((fd = open(filename, O_RDWR, 0664)) < 0);       // Open filename, if it doesn't exist, should return -1
        return (-1);
    while (ft_isblank(line[i]))
        i++;
    ft_memset(&(line[i]), ' ', ft_strlen(filename));	// overwritting filename with ' ' in line
    free(filename);
    return (fd);
}
/*
** Close_if: close fd specified as arg1
** if it is different from value in arg2
** return 0
*/
int
    close_if(int fd1, int diff)
{
    if (fd1 != diff)
        close(fd1);
    return (0);
}

/*
** Search for redirection symbols in *line
** Open/Create redirection files if they don't exist
** Set STDIN/STDOUT to redirection files fd if redirections are found
** Replaces redirections char and filenames in *line with blank spaces
** Sets saved_fd_redir to saved stdin/stdout fds
*/
int
	parse_redirections(char *line, int redirfd[2])
{
	int	i;

	i = 0;
	redirfd[0] = STDIN_FILENO;
	redirfd[1] = STDOUT_FILENO;
	while (line[i])
	{
		if (line[i] == '>')
		{
            if (redirfd[1] != STDOUT_FILENO)
                close(redirfd[1]);                              // If a file was already opened for an output redir, close it
            if ((redirfd[1] = parse_output_redir(&(line[i]))) < 0)
                return (close_if(redirfd[0], STDIN_FILENO) - 1);   // Closes input_redir file if one was open before returning
		}
        else if (line[i] == '<')
        {
            if (redirfd[0] != STDIN_FILENO)
                close(redirfd[0]);                              // If a file was already opened for an input redir, close it
            if ((redirfd[0] = parse_input_redir(&(line[i]))) < 0)
                return (close_if(redirfd[1], STDOUT_FILENO));
        }
		i++;
	}
    return (0);
}
/*    i = 0;
    if (in_redir_fd != STDIN_FILENO)
	{
        i += ((redir_io_saved_fd[0] = set_fd(in_redir_fd, STDIN_FILENO)) < 0);
        close(in_redir_fd);
    }    
    if (out_redir_fd != STDOUT_FILENO)
    {
        i += ((redir_io_saved_fd[1] = set_fd(out_redir_fd, STDOUT_FILENO)) < 0);	//Set STDIN to file_fd[0], if no redirections, it is set to 0  AND Set STDOUT to file_fd[1], if no redirections, it is set to 1
        close(out_redir_fd);
    }
    return (i * -1);
}
*/
/*
** Close redir files
** Set STDIN and STDOUT to redir_io_saved_fd
** Close redir_io_saved_fd's
*/

int
    reset_redirections(int redir_io_saved_fd[2])
{
    if (redir_io_saved_fd[0] != STDIN_FILENO)
    {
        if (reset_fd(redir_io_saved_fd[0], STDIN_FILENO) < 0)
            return (-1);
        close(redir_io_saved_fd[0]);
        redir_io_saved_fd[0] = STDIN_FILENO;
    }
    if (redir_io_saved_fd[1] != STDOUT_FILENO)
    {
        if (reset_fd(redir_io_saved_fd[1], STDOUT_FILENO) < 0)
            return (-1);
        close(redir_io_saved_fd[1]);
        redir_io_saved_fd[1] = STDOUT_FILENO;
    }
    return (0);
}