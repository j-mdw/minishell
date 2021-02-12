#include "minishell.h"

t_list
	*env_get_key(t_list *env, char *key)
{
	int key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (!(ft_strncmp(key, env->content, key_len)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
