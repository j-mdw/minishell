#include "termcaps.h"


static void
    dynamic_overwrite_first(char **arr, int arr_size, int str_size)
{
    int i;
    while (i < arr_size - 1)
    {
        arr[i] = arr[i + 1];
        i++;
    }
    ft_bzero(arr[arr_size - 1], str_size);
}

int
    dynamic_get_next_free(char **arr, int arr_size)
{   
    int index;

    index = 0;
    while (index < arr_size && *(arr[index]))
        index++;
    if (index == arr_size)
        return (-1);
    return(index);
}

char
    *dynamic_next_line(char **arr, int arr_size, int str_size)
{
    int index;

    if ((index = dynamic_get_next_free(arr, arr_size)) < 0)
    {
        dynamic_overwrite_first(arr, arr_size, str_size);
        return (arr[arr_size -1]);
    }
    else
        return (arr[index]);
}