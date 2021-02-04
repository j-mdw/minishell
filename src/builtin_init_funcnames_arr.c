#include "minishell.h"

char
	**builtin_init_funcnames_arr(void)
{
	char **arr;
	
	arr = (char **)malloc(sizeof(char *) * BUILTIN_COUNT + 1);

	arr[0] = ft_strdup("echo");
	arr[1] = ft_strdup("exit");
	arr[2] = ft_strdup("pwd");
	arr[3] = ft_strdup("env");
	arr[4] = ft_strdup("cd");
	arr[5] = ft_strdup("export");
	arr[6] = ft_strdup("unset");
	arr[7] = NULL;
	return (arr);
}