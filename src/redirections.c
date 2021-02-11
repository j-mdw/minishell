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
    if (!(filename = get_filename(&(line[i]))))	                            // Parsing of get_filename not final yet
        return (-1);
    if ((fd = open(filename, O_RDWR | O_CREAT | append_flag, 0664)) < 0)    // Open filename, if it doesn't exist, create it
    {
        free(filename);
        return (-1);
    }
    while (ft_isblank(line[i]))
        i++;
    ft_memset(&(line[i]), ' ', ft_strlen(filename));		                // overwritting filename with ' ' in line
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
    if ((fd = open(filename, O_RDWR, 0664)) < 0)       // Open filename, if it doesn't exist, should return -1
    {
        free(filename);
        return (-1);
    }
    while (ft_isblank(line[i]))
        i++;
    ft_memset(&(line[i]), ' ', ft_strlen(filename));	// overwritting filename with ' ' in line
    free(filename);
    return (fd);
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
                return (close_if(redirfd[1], STDOUT_FILENO) - 1);
        }
		i++;
	}
    return (0);
}
