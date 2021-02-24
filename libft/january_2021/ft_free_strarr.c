#include "libft.h"

/*
** Free string arr data
** Set *strarr to NULL
*/

void
	ft_free_strarr(char ***strarr)
{
	int	i;

	i = 0;
	while ((*strarr)[i])
	{
		free((*strarr)[i]);
		(*strarr)[i] = NULL;
		i++;
	}
	free(*strarr);
	*strarr = NULL;
}