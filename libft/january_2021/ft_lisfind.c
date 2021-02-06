#include "libft.h"

t_list
    *ft_lstfind(t_list *begin, void *content)
{
    while (begin)
    {
        if (!(ft_strcmp(begin->content, content)))
            return (begin);
        begin = begin->next;
    }
    return (NULL);
}