#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct termios g_origin_termios;

void
    fatal(char *err_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", err_msg, strerror(errno));
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        dprintf(STDERR_FILENO, "Error: tcsetattr: tty reset failed\n");
    exit(EXIT_FAILURE);
}


int
    main(void)
{
    struct termios  raw_termios;
    char            c;
    int             read_ret;

    if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
        fatal("tcgetattr");
    cfmakeraw(&raw_termios);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) < 0)
        fatal("tcsetattr");
    while (1)
    {
        if ((read_ret = read(STDIN_FILENO, &c, 1)) < 0)
            fatal("read");
        if (read_ret == 0)
            write(1, "bye\n", 4);
        write(STDIN_FILENO, &c, 1);
        printf("Char val: %d\n", c);
        if (c == ('q' & 0x1f))
            break;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios);
    return(EXIT_SUCCESS);
}
