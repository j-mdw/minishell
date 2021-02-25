#include "minishell.h"

/*
** Does not work properly when a SIGINT is received
** inside of a running process, as 'coquillage$>'
** gets written twice
*/

void
	sigint_handler(int sig_nb)
{
	write(1, "\nCoquillage(sigint)$>", 21);
	g_minishell_exit_status = 128 + sig_nb;
}

void
	sigint_parent_handler(int sig_nb)
{
	g_minishell_exit_status = 128 + sig_nb;
}

/*
** In bash, ctrl + \ (SIGQUIT) does not do anything
*/
void
	sigquit_handler(int sig_nb)
{
	(void)sig_nb;
}

void
	sigquit_parent_handler(int sig_nb)
{
	// write(STDIN_FILENO, "Quit (core dumped)\n", 19);
	g_minishell_exit_status = 128 + sig_nb;
}

void
    set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void
	set_parent_signals(void)
{
	signal(SIGINT, sigint_parent_handler);
	signal(SIGQUIT, sigquit_parent_handler);
}

void
	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
