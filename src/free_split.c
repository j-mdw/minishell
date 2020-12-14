
#include "minishell.h"

void
	free_split(char ***line_split)
{
	int	i;

	i = 0;
	while ((*line_split)[i])
	{
		free((*line_split)[i]);
		i++;
	}
	free(*line_split);
}