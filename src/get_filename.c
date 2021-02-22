#include "minishell.h"

char
	*get_filename(char *line)
{
	int		i;
    char    *filename;

	while (ft_isblank(*line))
        line++;
    i = 0;
    while (ft_isprint(line[i]) && line[i] != '<' && line[i] != '>' &&line[i] != ' ')      // TBU
        i++;
    if (i == 0)
    {
        printf("Syntax error");
        return (NULL);
    }
    if (!(filename = ft_substr(line, 0, i)))
        return (NULL);
    return (filename);
}