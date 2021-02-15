#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



void
    fatal(char *err_msg)
{
    dprintf(STDERR_FILENO, "Error: %s\n", err_msg);
    exit(EXIT_FAILURE);
}

void
    tty_raw(void)
{
    
}
int
    main(void)
{
    struct termios origin_termios;

    if (tcgetattr(STDIN_FILENO, &origin_termios) < 0)
        fatal("Can't get tty settings");
    tty_raw()
}
