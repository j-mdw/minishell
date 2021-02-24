#include "termcaps.h"

int
    main(void)
{
    char    *hist[HIST_SIZE];
    int     ret;
    int     i;

    i = 0;
    while (i < HIST_SIZE)
    {
        hist[i] = NULL;
        i++;
    }
    i = 0;
    // while (i < HIST_SIZE)
    // {
    //     printf("fuck you");
    //     dprintf(STDERR_FILENO, "HISTSIZE: %d|%p\n", i, hist[i]);
    //     // free(hist[i]);
    //     i++;
    // }
    while ((ret = tty_get_line(hist, HIST_SIZE)) >= 0)
    {
        (void)ret;
        // printf("line: %s| Ret: %d\n", hist[0], ret);
        // free(line);
    }
    i = 0;
    while (hist[i])
    {
        printf("%s\n", hist[i]);
        free(hist[i]);
        i++;
    }
    return (0);
}