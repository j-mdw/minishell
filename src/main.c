#include "minishell.h"

int
	main(void)
{
	char	*line;
	int		gnl_ret;

	set_signals();
	gnl_ret = 1;
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	while ((write(STDIN_FILENO, SHELL_MSG, ft_strlen(SHELL_MSG)) && \
		(gnl_ret = get_next_line(STDIN_FILENO, &line)) != 0))
	{
		if (gnl_ret < 0)
			fprintf(stderr, "%s\n", strerror(errno));		
		else if (*line != 0)
		{
			//Split on ';', to handle instruction groups independantly
			//Spilt? on pipes - Then open pipe, execute 1st cmd and write result from pipe
			//	then exec cmd 2, reading arg from pipe?
			// printf("%s\n", line); //Debug
			if (parse_input(line) < 0)
				printf("Error: %s\n", strerror(errno));
		}
		free(line);
	}
	free(line); // When gnl returns 0, 1 byte is still allocated on the heap	
	printf("exit\n");
	return (0);
}
