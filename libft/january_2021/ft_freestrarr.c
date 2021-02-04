#include "libft.h"

void
    ft_freestrarr(char **arr, int arr_size)
{
    int i;

    i = 0;
    while (i < arr_size)
    {
        write(STDOUT_FILENO, "Tra\n", 4);
        free(arr[i]);
        write(STDOUT_FILENO, "Tri\n", 4);
        i++;
    }
    free(arr);
}