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
    fd = open(filename, O_RDWR | O_CREAT | append_flag, 0664);   // Open filename, if it doesn't exist, create it
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
    line[i] = ' ';			// Overwritting redirection symbol
    i++;														
    if (!(filename = get_filename(&(line[i]))))	// Parsing of get_filename not final yet
        return (-1);
    fd = open(filename, O_RDWR, 0664);   // Open filename, if it doesn't exist, should return -1

    while (ft_isblank(line[i]))
        i++;
    ft_memset(&(line[i]), ' ', ft_strlen(filename));		// overwritting filename with ' ' in line
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
	parse_set_redirections(char *line, int redir_io_saved_fd[2], int redir_file_fd[2])
{
	int		i;

	i = 0;
	redir_file_fd[0] = STDIN_FILENO;
	redir_file_fd[1] = STDOUT_FILENO;
	while (line[i])
	{
		if (line[i] == '>')
		{
            if (redir_file_fd[1] != STDOUT_FILENO)
                close(redir_file_fd[1]);                              // If a file was already opened for an output redir, close it
            if ((redir_file_fd[1] = parse_output_redir(&(line[i]))) < 0)
                return (-1);
		}
        else if (line[i] == '<')
        {
            if (redir_file_fd[0] != STDIN_FILENO)
                close(redir_file_fd[1]);                              // If a file was already opened for an input redir, close it
            if ((redir_file_fd[0] = parse_input_redir(&(line[i]))) < 0)
                return (-1);
        }
		else
			i++;
	}
	if ((redir_io_saved_fd[0] = set_fd(STDIN_FILENO, redir_file_fd[0])) < 0 || \
	(redir_io_saved_fd[1] = set_fd(STDOUT_FILENO, redir_file_fd[1])) < 0)	//Set STDIN to file_fd[0], if no redirections, it is set to 0  AND Set STDOUT to file_fd[1], if no redirections, it is set to 1
        return (-1);    
    return (0);
}

/*
** Close redir files
** Set STDIN and STDOUT to redir_io_saved_fd
** Close redir_io_saved_fd's
*/

int
    reset_redirections(int redir_io_saved_fd[2], int redir_file_fd[2])
{
    if (redir_file_fd[0] != STDIN_FILENO)
    {
        close(redir_file_fd[0]);
        if (reset_fd(redir_io_saved_fd[0], STDIN_FILENO) < 0)
            return (-1);
        close(redir_io_saved_fd[0]);
    }
    if (redir_io_saved_fd[1] != STDOUT_FILENO)
    {
        close(redir_file_fd[1]);
        if (reset_fd(redir_io_saved_fd[1], STDOUT_FILENO) < 0)
            return (-1);
        close(redir_io_saved_fd[1]);
    }
    return (0);
}




/*
** Function: redir_input
** Redirects the output of cmd to filename;
** Appends the output to filename or
** replaces the content of filename with the output of cmd depending
** on append_flag, which should either be O_APPEND or O_TRUNC
** Return 0 on sussess, -1 if error


int
    redir_output(char **cmd, char *filename, int append_flag)
{
    int file_fd;
    int saved_fd;
    int ret;

    if (append_flag != O_APPEND && append_flag != O_TRUNC)
        printf("Wrong flag\n");                                                 // Not sure if need to keep this step
    if ((file_fd = open(filename, O_RDWR | O_CREAT | append_flag, 0664)) < 0)   // Open filename, if it doesn't exist, create it
    {
        printf("Error in redir_output: %s\n", strerror(errno));
        return (-1);
    }
    if ((saved_fd = set_fd(STDOUT_FILENO, file_fd)) < 0)                        // Set stdout to file_fd
        return (-1);
    if ((ret = exec_builtin(cmd)) < 0)
        printf("Error in redir_output - exec_builtin: %s\n", strerror(errno));
    reset_fd(saved_fd, STDOUT_FILENO);                                          // Reset stdout to 1
    if (close(file_fd) < 0)                                                     // Close file_fd
    {
        printf("Error in redir_output: %s\n", strerror(errno));
        return (-1);
    }
    return (ret);
}
*/
/*
** Function: redir_input
** Redirects the input of cmd to be filename;


int
    redir_input(char **cmd, char *filename)
{
    int file_fd;
    int saved_fd;
    int ret;

    if ((file_fd = open(filename, O_RDONLY)) < 0)                               // Open filename, error if does not exist
    {
        printf("Error in redir_input: %s\n", strerror(errno));
        return (-1);
    }
    if ((saved_fd = set_fd(STDIN_FILENO, file_fd)) < 0)                         // Set stdin to file_fd
        return (-1);
    if ((ret = exec_builtin(cmd)) < 0)
        printf("Error in redir_intput - exec_builtin: %s\n", strerror(errno));
    if ((reset_fd(saved_fd, STDIN_FILENO)) < 0)                                 // Reset stdin to 0
        return (-1);
    if (close(file_fd) < 0)                                                     // Close file_fd
        printf("Error in redir_input: %s\n", strerror(errno));
    return (ret);
}
*/
// int main(void)
// {
//     char *cmd1[3] = {"ls", "-la", NULL};

//     redir_output(cmd1, "Redir_tst", O_TRUNC);

//     char *cmd2[3] = {"cat", "-e", NULL};
//     redir_input(cmd2, "Redir_tst");
//     return (0);
// }
