/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:17:39 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/25 15:04:27 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint_handler(int sig_nb)
{
	write(1, "\nCoquillage$>", 13);
	g_minishell_exit_status = 128 + sig_nb;
}

void
	sigint_parent_handler(int sig_nb)
{
	write(1, "\n", 1);
	g_minishell_exit_status = 128 + sig_nb;
}

void
	sigquit_handler(int sig_nb)
{
	(void)sig_nb;
}

void
	sigquit_parent_handler(int sig_nb)
{
	write(STDIN_FILENO, "Quit (core dumped)\n", 19);
	g_minishell_exit_status = 128 + sig_nb;
}
