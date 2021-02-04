#include "minishell.h"

char
	**builtin_init_names_arr(void)
{
	char **arr;
	
	if (!(arr = (char **)malloc(sizeof(char *) * BUILTIN_COUNT + 1)))
		return (NULL);
	if (!(arr[0] = ft_strdup("echo")))
	{
		free(arr);
		return (NULL);
	}
	if (!(arr[1] = ft_strdup("exit")))
	{
		ft_freestrarr(arr, 1);
		return (NULL);
	}
	if (!(arr[2] = ft_strdup("pwd")))
	{
		ft_freestrarr(arr, 2);
		return (NULL);
	}
	if (!(arr[3] = ft_strdup("env")))
	{
		ft_freestrarr(arr, 3);
		return (NULL);
	}
	if (!(arr[4] = ft_strdup("cd")))
	{
		ft_freestrarr(arr, 4);
		return (NULL);
	}
	if (!(arr[5] = ft_strdup("export")))
	{
		ft_freestrarr(arr, 5);
		return (NULL);
	}
	if (!(arr[6] = ft_strdup("unset")))
	{
		ft_freestrarr(arr, 6);
		return (NULL);
	}
	arr[7] = NULL;
	return (arr);
}