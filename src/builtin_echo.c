/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:26:24 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/23 16:22:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_echo(char **arg, t_list **env)
{
	int n_flag;
	int i;

	(void)env;
	n_flag = 0;
	if (arg[1] && !(ft_strcmp(arg[1], "-n")))
		n_flag = 1;
	i = 1 + n_flag;
	while (arg[i])
	{
		write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
