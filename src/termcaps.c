#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


/* Notes:

Gestion curseur:
    - Fleches bas/haut:
        - Navigation dans l'historique: a chaque fois avant d'envoyer une ligne, la sauvegarder dans une liste
        - ctrl + haut / ctrl + bas permettent de se deplacer de haut en bas dans la limite de l'index column de base
    - Fleches cotes: comportement naturel - check position du curseur (pas plus a gauche que 
    la position de base, et pas plus a droite que le dernier char + 1)
    - Edition de ligne: sauvegarder les char en buffer dans l'order dans lequel ils sont recus
    et en cas d'input printable a un index qui contient deja des char, recize l'array, ajouter le char et write
    a partir du nouveau char

*/

struct termios g_origin_termios;

void
    fatal(char *err_msg)
{
    dprintf(STDERR_FILENO, "Error: %s: %s\n", err_msg, strerror(errno));
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        dprintf(STDERR_FILENO, "Error: tcsetattr: tty reset failed\n");
    exit(EXIT_FAILURE);
}

void
    tty_set_raw_mode(struct termios *raw_termios)
{
    cfmakeraw(raw_termios);
    raw_termios->c_lflag &= ~(ICANON | ECHO);
    raw_termios->c_lflag |= ISIG;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, raw_termios) < 0)
        fatal("tcsetattr");
}

int
    main(void)
{
    struct termios  raw_termios;
    char            c;
    int             read_ret;

    if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
        fatal("tcgetattr");
    raw_termios = g_origin_termios;
    tty_set_raw_mode(&raw_termios);
    while (1)
    {
        if ((read_ret = read(STDIN_FILENO, &c, 1)) < 0)
            fatal("read");
        if (read_ret == 0)
            write(1, "bye\n", 4);
        write(STDIN_FILENO, &c, 1);
        // printf("%d", c);
        if (c == ('q' & 0x1f))
            break;
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_origin_termios);
    return(EXIT_SUCCESS);
}
