#include "minishell.h"

char
	*env_get_val(t_list *env, char *key)
{
	char *value;

	while (env)
	{
		if ((value = ft_strchr(env->content, '=')))
		{
			if (!(ft_strncmp(key, env->content, value - (char *)env->content)))
				return (value + 1);
		}
		env = env->next;
	}
	return (NULL);
}
