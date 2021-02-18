#include "minishell.h"

int
	builtin_init_data_struct(t_builtin *builtin_data, char **env)
{
	if (!(builtin_data->local_env = env_create_list(env)))
		return (-1);
	if (!(builtin_data->builtin_names_arr = builtin_init_names_arr()))
	{
		ft_lstclear(&(builtin_data->local_env), free);
		return (-1);
	}
	builtin_init_funcarr(builtin_data->builtin_func_arr);
	return (0);
}