/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:43:45 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 16:43:09 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps_bonus.h"

static void
	send_line(char *newline, t_builtin *builtin_data)
{
	char	*err_string;
	char	*line;

	if ((line = ft_strdup(newline)))
	{
		errno = 0;
		if ((err_string = first_read(line)))
			dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s\'\n",
			err_string);
		else if (parse_input(line, builtin_data) < 0)
		{
			if (errno != 0)
				printf("Error: %s\n", strerror(errno));
			g_minishell_exit_status = 127;
		}
	}
	free(line);
}

int
	main(int ac, char **av, char **env)
{
	t_builtin		builtin_data;
	char			*hist[HIST_SIZE];
	int				hist_index;
	int				i;
	int				read_ret;

	(void)ac;
	(void)av;
	i = 0;
	while (i < HIST_SIZE)
		hist[i++] = NULL;
	set_signals();
	if (builtin_init_data_struct(&builtin_data, env) < 0)
		return (EXIT_FAILURE);
	while ((read_ret = read(0, NULL, 0)) == 0 && \
	(hist_index = tty_get_line(hist, HIST_SIZE)) >= 0)
		send_line(hist[hist_index], &builtin_data);
	i = 0;
	while (hist[i])
		free(hist[i++]);
	builtin_free_data_struct(&builtin_data);
	if (read_ret == 0)
		printf("exit\n");
	return (g_minishell_exit_status);
}
