#include "minishell.h"

int
	execute_builtin(char **arg_split)
{
	pid_t	child;
	int		wstatus; //passed to wait
	char	*file_path;
	
	file_path = NULL;
	if ((child = fork()) < 0)
		fprintf(stderr, "%s\n", strerror(errno));
	else if (child == 0)
	{
		printf("Child: \n"); //For Debug purposes
		if ((file_path = ft_strjoin(BIN_PATH, arg_split[0])) == NULL)
			return (printf("Join error\n")); //error_free
		execve(file_path, arg_split, NULL);
		fprintf(stderr, "%s\n", strerror(errno));
	}
	else
	{
		printf("Pid: %d\n", wait(&wstatus));
		printf("Goodbye from parent!\n");
		free(file_path);
	}
	return (0);
}

int
	parse_input(char *line, char ***line_split)
{

	if (!(*line_split = ft_split(line, ' '))) //Clement: use macro for ' '?
	{
		return (-1);
	}
	if (*line_split == NULL)	//Empty line, but may be useless considering we don't read unless we receive a \n from stdin??
	{
		printf("Empty line");
		return (0);
	}
	// + Check len and max arg here!
	// + Check if 1st arg of split is NULL
	/*
	** Check 1st arg:
	**	if built-in cmd: return BUILT_IN_CMD
	**	if local cmd (one we have to manage ourselves): return LOCAL_CMD
	**	else: set errno; return -1
	*/
	return (BUILT_IN_CMD);
}

void
	free_split(char ***line_split)
{
	int	i;

	i = 0;
	while ((*line_split)[i])
	{
		free((*line_split)[i]);
		i++;
	}
	free(*line_split);
}

int
	main(void)
{
	char	*line;
	char	**line_split;
	int		gnl_ret;
	int		split_ret;

	while (1)
	{
		write(STDIN_FILENO, "Coquillage $>", 13);
		if ((gnl_ret = get_next_line(STDIN_FILENO, &line)) < 0)
			fprintf(stderr, "%s\n", strerror(errno));		
		else
		{
			if ((split_ret = parse_input(line, &line_split)) < 0)
				fprintf(stderr, "%s\n", strerror(errno));
			else if (split_ret == BUILT_IN_CMD)
				execute_builtin(line_split);
		}
		free(line);
		free_split(&line_split);
	}	
	return (0);
}
