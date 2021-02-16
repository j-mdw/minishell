/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:27:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/14 13:27:07 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin_exit(char **cmd, t_list **env)
{
	(void)cmd;
	(void)env;
	close(STDIN_FILENO);
	return (EXIT_SUCCESS);
}
