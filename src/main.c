/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:50:31 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/16 15:40:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	init_builtin_data_struct(t_builtin *builtin_data, char **env)
{
	if (!(builtin_data->local_env = env_create_list(env)))
		return (-1);
	if (!(builtin_data->builtin_names_arr = builtin_init_names_arr()))
	{
		ft_lstclear(&(builtin_data->local_env), free);
		return (-1);
	}
	builtin_init_funcarr(builtin_data->builtin_func_arr);
	return (0);
}

void
	free_builtin_data_struct(t_builtin *builtin_data)
{
	ft_free_strnarr(builtin_data->builtin_names_arr, BUILTIN_COUNT);
	ft_lstclear(&(builtin_data->local_env), free);
}

// int	g_minishell_exit_status;

int
	main(int ac, char **av, char **env)
{
	char			*line;
	int				gnl_ret;
	int				exit_status;
	t_builtin		builtin_data;
	char	*err_string;

	(void)ac;
	(void)av;
	set_signals();
	if (init_builtin_data_struct(&builtin_data, env) < 0)
		return (-1);
	//The below stops looping when a EOF is read - only way to send a EOF through stdin
	//seems to be through ctrl + D, which is an option we have to handle
	gnl_ret = 1;
	while ((write(STDIN_FILENO, SHELL_MSG, ft_strlen(SHELL_MSG))
		&& (gnl_ret = get_next_line(STDIN_FILENO, &line)) > 0))
	{
		// if (gnl_ret < 0)
		// 	fprintf(stderr, "GNL error: %s\n", strerror(errno));		
		if (*line != 0)
		{
			if ((err_string = first_read(line)))
				printf("minishell: syntax error near unexpected token `%s\'\n", err_string);
			else if ((exit_status = parse_input(line, &builtin_data)) < 0)
				printf("Error: %s\n", strerror(errno));
			printf("Exit status: %d\n", g_minishell_exit_status);
		}
		free(line);
	}
	free(line); // When gnl returns 0, 1 byte is still allocated on the heap
	free_builtin_data_struct(&builtin_data);
	printf("exit\n");
	return (0);
}
