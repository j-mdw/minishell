#include "minishell.h"

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
