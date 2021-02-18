/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:50:31 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/15 15:57:38 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int ac, char **av, char **env)
{
	char			*line;
	int				gnl_ret;
	t_builtin		builtin_data;

	(void)ac;
	(void)av;
	set_signals();
	if (builtin_init_data_struct(&builtin_data, env) < 0)
		return (-1);
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	gnl_ret = 1;
	while ((write(STDIN_FILENO, SHELL_MSG, ft_strlen(SHELL_MSG))
		&& (gnl_ret = get_next_line(STDIN_FILENO, &line)) > 0))
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
