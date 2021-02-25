#include "minishell.h"

void
	builtin_free_data_struct(t_builtin *builtin_data)
{
	ft_free_strnarr(builtin_data->builtin_names_arr, BUILTIN_COUNT);
	ft_lstclear(&(builtin_data->local_env), free);
}