#include "termcaps.h"

int
    tty_set_raw_mode(struct termios *raw_termios)
{
    cfmakeraw(raw_termios);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, raw_termios) < 0)
        return(tty_error("tcsetattr"));
    return (0);
}