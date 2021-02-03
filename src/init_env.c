#include "minishell.h"
/*
typedef struct  s_dico {
    void                *key;
    void                *value;
    struct s_dico    *next;
}               t_dico;

void
	dico_add_back(t_dico **alst, t_dico *new)
{
	t_dico	*last;

	if (!(*alst))
        *alst = new;
	else
    {
        last = *alst;
        while (last->next)
            last = last->next;
	    last->next = new;
    }
}

void
    putexport(t_dico *elem)
{
    if (elem->key)
    {
        write(STDOUT_FILENO, "declare -x ", 11);
        write(STDOUT_FILENO, elem->key, ft_strlen(elem->key));
    }
    if (elem->value)
    {
        write(STDOUT_FILENO, "=", 1);
        write(STDOUT_FILENO, "\"", 1);
        write(STDOUT_FILENO, elem->value, ft_strlen(elem->value));
        write(STDOUT_FILENO, "\"", 1);
    }
    write (STDOUT_FILENO, "\n", 1);
}

void
    dico_iter(t_dico *lststart, void (*f)(t_dico *))
{
    while (lststart)
    {
        (*f)(lststart);
        lststart = lststart->next;
    }
}

int
    dico_remove(t_dico **start, void *cmp)
{
    t_dico  *trailing_elem;

    if (!start)
        return (-1);
    trailing_elem = *start;
    while (ft_strcmp(cmp, (*start)->key) != 0)
    {
        trailing_elem = *start;
        *start = (*start)->next;
            trailing_elem->next = (*start)->next;
            dico_delone(*start, free);
        }

    }
}

void
	dico_delone(t_dico *dico, void (*del)(void *))
{
	if (dico && del)
    {
	    (*del)(dico->key);
        (*del)(dico->value);
    }
    free(dico);
}

void
    dico_clear(t_dico **start)
{
    t_dico  *next_elem;

    next_elem = *start;
    while (next_elem)
    {
        next_elem = next_elem->next;
        dico_delone(*start, free);
        *start = next_elem;
    }
}

t_dico
    *dico_lstnew(char *key, char *value)
{  
    t_dico   *new_elem;

    if (!(new_elem = (t_dico *)malloc(sizeof(t_dico))))
        return (NULL);
    new_elem->key = key;
    new_elem->value = value;
    new_elem->next = NULL;
    return (new_elem);
}

t_dico
    *init_local_env(char **env)
{
    t_dico   *local_env;
    t_dico   *new_elem;
    int         i;
    int         j;
    int         k;

    i = 0;
    local_env = NULL;
    while(env[i])
    {
        if (!(new_elem = dico_lstnew(NULL, NULL)))
            return (NULL);
        j = 0;
        while (env[i][j] != '=' && env[i][j])
            j++;
        if (!(new_elem->key = ft_strndup(env[i], j)))
            return (NULL); // need to free list before
        if (env[i][j])
        {
            j += 1;
            k = 0;
            while (env[i][j + k])
                k++;
            if (!(new_elem->value = ft_strndup(env[i] + j, k)))
                return (NULL); // need to free list before
        }
        dicoadd_back(&local_env, new_elem);
        i++;     
    }
    return (local_env);
}

int main(int ac, char **av, char **env)
{
    t_dico   *local_env;

    if (!(local_env = init_local_env(env)))
        printf("Init local env error\n");
    else
        dico_iter(local_env, putexport);
    return (0);
}

*/
// env_create_lst - create list based on **env
// env_add_var -   add new env var to list
// env_del_var - remove var from list
// env_search - search for key and return pointer to elem
// env_arr - create an arr of str based from the list

char
    *env_get_val(t_list *env, char *key)
{
    char *value;

    while (env)
    {
        if ((value = ft_strchr(env->content, '=')))
        {
            if (!(ft_strncmp(key, env->content, value - (char *)env->content)))
                return (value);
        }
        env = env->next;
    }
    return (NULL);
}

void
    env_print(t_list *local_env)
{
    while (local_env)
    {
        printf("%s\n", local_env->content);
        local_env = local_env->next;
    }
}

void
    ft_list_remove_if(t_list **begin_list, void *data_ref, void (*free_fct)(void *))
{
    t_list  *list_iter;
    t_list  *store;
    size_t  data_ref_len;

    if (!begin_list || !*begin_list || !data_ref || !free_fct)
        return ;
    list_iter = *begin_list;
    data_ref_len = ft_strlen(data_ref);
    store = *begin_list;
    while (list_iter)
    {
        if (!ft_strncmp(data_ref, list_iter->content, data_ref_len))
        {
            free_fct(list_iter->content);
            if (store == *begin_list)
            {
                list_iter = list_iter->next;
                free_fct(store);
                *begin_list = list_iter;
                store = *begin_list;
            }
            else
            {
                list_iter = list_iter->next;         
                free_fct(store->next);
                store->next = list_iter;
            }
        }
        else
        {
            store = list_iter;
            list_iter = list_iter->next;
        }
    }
}

char
    **env_set_arr(t_list *local_env_lst)
{
    char    **local_env_arr;
    int     lst_size;
    int     i;

    lst_size = ft_lstsize(local_env_lst);
    if (!(local_env_arr = (char **)malloc(sizeof(char *) * (lst_size + 1))))
        return (NULL);
    i = 0;
    while (i < lst_size)
    {
        local_env_arr[i] = local_env_lst->content;
        local_env_lst = local_env_lst->next;
        i++;
    }
    local_env_arr[i] = NULL;
    return (local_env_arr);
}

t_list
    *env_create_lst(char **env)
{
    t_list  *local_env;
    t_list  *new_elem;
    int     i;

    i = 0;
    local_env = NULL;
    while(env[i])
    {
        if (!(new_elem = ft_lstnew(ft_strdup(env[i])))) // Create a new element and a copy of the env variable (heap memory)
            return (NULL);  // Need to clear list
        ft_lstadd_back(&local_env, new_elem);
        i++;     
    }
    return (local_env);
}

main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    
    t_list *local_env = env_create_lst(env);
    printf("\n\nFROM ENV PRINT:\n\n");
    env_print(local_env);
    printf("\n\nFROM PRINT ARR:\n\n");
    ft_putstrarr(env_set_arr(local_env));

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
    printf("PWD: %s | PATH: %s | TITI: %s\n", env_get_val("PWD"), env_get_val("PATH"));
    ft_lstclear(&local_env, free);
}