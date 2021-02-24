#include "minishell.h"

int main(int ac , char ** av, char **env)
{
	t_lit_status lit_status;

	lit_status_init(&lit_status);
	char *str = ft_strdup(av[1]);
	// int i =0;
	t_list *local_env = env_create_list(env);
	// first_read)
	char *pilou = param_trim(str, local_env);
	printf("|%s|\n", pilou);
	free(pilou);
	// while (str[i])
	// {
	// 	printf("char: %c status: %d\n", str[i], is_lit(str[i], &lit_status));
	// 	i++;
	// }
	ft_lstclear(&local_env, free);
	free(str);
	return(0);
}
