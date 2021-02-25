/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:49:41 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 10:49:43 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exec_set_redir(int redirfd[2])
{
	if (redirfd[0] != STDIN_FILENO)
	{
		if (dup2(redirfd[0], STDIN_FILENO) < 0)
			dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	}
	if (redirfd[1] != STDOUT_FILENO)
	{
		if (dup2(redirfd[1], STDOUT_FILENO) < 0)
			dprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
	}
}
