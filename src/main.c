#include "minishell.h"

int
	main(int ac, char **av, char **env)
{
	char	*line;
	int		gnl_ret;
	int		exit_status;

	(void)ac;
	(void)av;
	(void)env;
	set_signals();
	gnl_ret = 1;
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	while ((write(STDIN_FILENO, SHELL_MSG, ft_strlen(SHELL_MSG)) && \
		(gnl_ret = get_next_line(STDIN_FILENO, &line)) != 0))
	{
		if (gnl_ret < 0)
			fprintf(stderr, "GNL error: %s\n", strerror(errno));		
		else if (*line != 0)
		{
			if ((exit_status = parse_input(line, env)) < 0)
				printf("Error: %s\n", strerror(errno));
		}
		free(line);
	}
	free(line); // When gnl returns 0, 1 byte is still allocated on the heap	
	printf("exit\n");
	return (0);
}
