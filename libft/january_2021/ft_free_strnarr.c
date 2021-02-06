#include "libft.h"

void
    ft_free_strnarr(char **arr, int arr_size)
{
    int i;

    i = 0;
    while (i < arr_size)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}