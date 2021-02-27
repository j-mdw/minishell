/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:27:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/27 13:52:47 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_exit(char **cmd, t_list **env)
{
	int i;

	(void)env;
	i = 0;
	printf("exit\n");
	while (cmd[i])
		i++;
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	if (i == 1)
		return (EXIT_SUCCESS);
	i = 0;
	while (ft_isdigit(cmd[1][i]))
		i++;
	if (cmd[1][i] != '\0')
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (2);
	}
	return (ft_atoi(cmd[1]) & 0377);
}
