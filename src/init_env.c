#include "minishell.h"

main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    
    t_list *local_env = env_create_list(env);
    printf("\n\nFROM ENV PRINT:\n\n");
    env_print(local_env);
    printf("\n\nFROM PRINT ARR:\n\n");
    ft_putstrarr(env_make_arr(local_env));

    char *toto = malloc(10);
    char *tata = malloc(10);
    ft_strcpy(toto, "TITI=toto");
    ft_strcpy(tata, "TITI=tata");
    ft_lstadd_front(&local_env, ft_lstnew(toto));
    ft_lstadd_back(&local_env, ft_lstnew(tata));
    printf("\n\n TITI:\n\n");    
    env_print(local_env);
    ft_list_remove_if(&local_env, "TITI", free);
    printf("\n\n TITI REMOVED:\n\n");
    env_print(local_env);
    printf("PWD: %s\nPATH: %s\nTITI: %s\n", env_get_val(local_env, "PWD"), env_get_val(local_env, "PATH"), env_get_val(local_env, "TITI"));
    ft_lstclear(&local_env, free);
}