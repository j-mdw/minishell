#include "libft.h"

static void
    set_elem(t_list **begin_list, t_list *list_iter, t_list *store, void (*free_fct)(void *))
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

void
    ft_list_remove_if(t_list **begin_list, void *data_ref, \
	void (*free_fct)(void *))
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
            set_elem(begin_list, list_iter, store, free_fct);
            // free_fct(list_iter->content);
            // if (store == *begin_list)
            // {
            //     list_iter = list_iter->next;
            //     free_fct(store);
            //     *begin_list = list_iter;
            //     store = *begin_list;
            // }
            // else
            // {
            //     list_iter = list_iter->next;
            //     free_fct(store->next);
            //     store->next = list_iter;
            // }
        }
        else
        {
            store = list_iter;
            list_iter = list_iter->next;
        }
    }
}
