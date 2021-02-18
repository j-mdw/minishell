#include "minishell.h"
#include "termcaps/termcaps.h"

int
	main(int ac, char **av, char **env)
{
	char			*line;
	t_builtin		builtin_data;

	(void)ac;
	(void)av;
	set_signals();
	if (builtin_init_data_struct(&builtin_data, env) < 0)
		return (-1);
	while ((tty_get_line(&line) >= 0))
	{		
		if (*line != 0)
		{
			errno = 0;
			if (parse_input(line, &builtin_data) < 0)
			{
				if (errno != 0)
					dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
				g_minishell_exit_status = 127;
			}
			printf("Exit status: %d\n", g_minishell_exit_status);
		}
		free(line);
	}
	free(line); // When gnl returns 0, 1 byte is still allocated on the heap
	builtin_free_data_struct(&builtin_data);
	printf("exit\n");
	return (0);
}