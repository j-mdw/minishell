#include "minishell.h"

char
    **parse_argv(char *cmd_line)
{
    char **argv;

    argv = ft_split(cmd_line, ' ');
    return (argv);
}