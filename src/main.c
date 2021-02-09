#include "minishell.h"

int
	main(int ac, char **av, char **env)
{
	char			*line;
	int				gnl_ret;
	int				exit_status;
	t_builtin		builtin_data;

	(void)ac;
	(void)av;
	set_signals();
	if (!(builtin_data.local_env = env_create_list(env)))
		return (-1);
	if (!(builtin_data.builtin_names_arr = builtin_init_names_arr()))
	{
		ft_lstclear(&(builtin_data.local_env), free);
		return (-1);
	}
	builtin_init_funcarr(builtin_data.builtin_func_arr);
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	gnl_ret = 1;
	while ((write(STDIN_FILENO, SHELL_MSG, ft_strlen(SHELL_MSG))
		&& (gnl_ret = get_next_line(STDIN_FILENO, &line)) != 0))
	{
		if (gnl_ret < 0)
			fprintf(stderr, "GNL error: %s\n", strerror(errno));		
		else if (*line != 0)
		{
			if ((exit_status = parse_input(line, &builtin_data)) < 0)
				printf("Error: %s\n", strerror(errno));
		}
		free(line);
	}
	free(line); // When gnl returns 0, 1 byte is still allocated on the heap
	ft_free_strnarr(builtin_data.builtin_names_arr, BUILTIN_COUNT);
	ft_lstclear(&(builtin_data.local_env), free);
	printf("exit\n");
	return (0);
}
