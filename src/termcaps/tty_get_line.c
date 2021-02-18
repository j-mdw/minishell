#include "termcaps.h"

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

int
    tty_get_line(char **line)
{
    struct termios  raw_termios;
    t_cursor_pos    cursor_pos;
    int             ret;

    *line = NULL;
    if (tcgetattr(STDIN_FILENO, &g_origin_termios) < 0)
        return(tty_error("tcgetattr"));
    raw_termios = g_origin_termios;
    if (tty_set_raw_mode(&raw_termios) < 0)
        return (-1);
    if (tty_newline(&cursor_pos) < 0)
        return (-1);
    if ((ret = tty_read_echo(&cursor_pos, line)) < 0)
    {
        free(*line);
        *line = NULL;
    }
    if (tcsetattr(STDIN_FILENO, TCSANOW, &g_origin_termios) < 0)
        return (tty_error("tty reset failed"));
    return(ret);
}

int
    main(void)
{
    char *line;
    int  ret;
    
    while ((ret = tty_get_line(&line)) >= 0)
    {
        printf("line: %s| Ret: %d\n", line, ret);
        free(line);
    }
    return (0);
}