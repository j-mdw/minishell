#include "libft.h"

void
    ft_putstrarr(char **arr)
{
    int i;

    if (arr)
    {
        i = 0;
        while (arr[i])
        {
            ft_putstr_fd(arr[i], STDOUT_FILENO);
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
    }
}
