#include "termcaps.h"


static void
    dynamic_overwrite_first(char **arr, int arr_size)
{
    int i;

    free(arr[0]);
    i = 0;
    while (i < arr_size - 1)
    {
        arr[i] = arr[i + 1];
        i++;
    }
    arr[i] = NULL;
}

static int
    dynamic_get_next_free(char **arr, int arr_size)
{   
    int index;

    index = 0;
    while (index < arr_size && arr[index])
        index++;
    if (index == arr_size)
        return (-1);
    return(index);
}

int
    dynamic_next_line(char **arr, int arr_size)
{
    int index;

    if ((index = dynamic_get_next_free(arr, arr_size)) < 0)
    {
        dynamic_overwrite_first(arr, arr_size);
        return (arr_size -1);
    }
    return (index);
}