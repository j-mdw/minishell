#include "minishell.h"
#include "termcaps.h"

int
	main(int ac, char **av, char **env)
{
	t_builtin		builtin_data;
	char			*line;
	char			*err_string;
	char			*hist[HIST_SIZE];
	int				hist_index;
	int				i;

	(void)ac;
	(void)av;
	i = 0;
	while (i < HIST_SIZE)
	{
		hist[i] = NULL;
		i++;
	}
	set_signals();
	if (builtin_init_data_struct(&builtin_data, env) < 0)
		return (-1);
	while ((hist_index = tty_get_line(hist, HIST_SIZE)) >= 0)
	{		
		if ((line = ft_strdup(hist[hist_index])))
		{
			errno = 0;
			if ((err_string = first_read(line)))
				dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `%s\'\n", err_string);
			if (parse_input(line, &builtin_data) < 0)
			{
				if (errno != 0)
					dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
				g_minishell_exit_status = 127;
			}
		}
		free(line);
	}
	i = 0;
	while (hist[i])
	{
		free(hist[i]);
		i++;
	}
	builtin_free_data_struct(&builtin_data);
	printf("exit\n");
	return (0);
}