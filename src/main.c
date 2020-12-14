#include "minishell.h"

int
	main(void)
{
	char	*line;
	char	**line_split;
	int		gnl_ret;
	int		split_ret;

	set_signals();
	gnl_ret = 1;
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	while ((write(STDIN_FILENO, SHELL_MSG, SHELL_MSG_LEN) && \
		(gnl_ret = get_next_line(STDIN_FILENO, &line)) != 0))
	{
		if (gnl_ret < 0)
			fprintf(stderr, "%s\n", strerror(errno));		
		else if (*line != 0)
		{	
			if ((split_ret = parse_input(line, &line_split)) < 0)
				fprintf(stderr, "%s\n", strerror(errno));
			else if (split_ret == BUILT_IN_CMD)
				exec_builtin(line_split);
			free_split(&line_split);
		}
		free(line);
	}	
	return (0);
}
