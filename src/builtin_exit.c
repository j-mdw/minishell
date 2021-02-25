/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:27:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 11:52:12 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_exit(char **cmd, t_list **env)
{
	(void)env;
	close(STDIN_FILENO);
	if (cmd[1])
		return (ft_atoi(cmd[1]));
	return (EXIT_SUCCESS);
}
