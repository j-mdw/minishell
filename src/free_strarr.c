
#include "minishell.h"

/*
** Free string arr data
** Set *strarr to NULL
*/

void
	free_strarr(char ***strarr)
{
	int	i;

	i = 0;
	while ((*strarr)[i])
	{
		free((*strarr)[i]);
		i++;
	}
	free(*strarr);
	*strarr = NULL;
}