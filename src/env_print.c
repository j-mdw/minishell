#include "minishell.h"

void
    env_print(t_list *local_env)
{
    while (local_env)
    {
        printf("%s\n", local_env->content);
        local_env = local_env->next;
    }
}