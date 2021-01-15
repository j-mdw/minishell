
#include "minishell.h"

/*
** Free split data
** Set *split to NULL
*/

void
	free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
}