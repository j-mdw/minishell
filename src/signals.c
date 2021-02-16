#include "minishell.h"

/*
** Does not work properly when a SIGINT is received
** inside of a running process, as 'coquillage$>'
** gets written twice
*/

void
	sigint_handler(int sig_nb)
{
	sig_nb++;
	write(1, "\n", 1);
	// write(1, "\nCoquillage(sigint)$>", 21);
}

/*
** In bash, ctrl + \ (SIGQUIT) does not do anything
** ^\ does not even get written to stdin, don't know
** yet how to do this
*/
void
	sigquit_handler(int sig_nb)
{
	sig_nb++;
}

void
    set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void
	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
