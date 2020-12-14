#include "minishell.h"

int
	main(void)
{
	pid_t	child;
	char	*line;
	int		gnl_ret;
	char	**input_split;
	char	*file_path;

	while (1)
	{
		write(STDIN_FILENO, "Coquillage $>", 13);
		//Need considerations for MAX_ARGS and MAX_ARG_STRLEN
		if ((gnl_ret = get_next_line(STDIN_FILENO, &line)) < 0)
			fprintf(STDERR_FILENO, "%s\n", strerror(errno));		
		else
		{	
			if ((child = fork()) < 0)
			{
				fprintf(STDERR_FILENO, "%s\n", strerror(errno));
			}
			else if (child == 0)
			{
				printf("Child: \n");
				if (!(input_split = ft_split(line, ' ')))
					return(printf("Split error\n")); //error_free
				if (*input_split == NULL)
					return (printf("Empty line\n")); //error_free
				if ((file_path = ft_strjoin(BIN_PATH, input_split[0])) == NULL)
					return (printf("Join error\n")); //error_free
				execve(file_path, input_split, NULL);
				printf("%s\n", strerror(errno));
			}
			else
				printf("Hello from parent!\n");
			free(line);
		}
	}	
	return (0);
}
