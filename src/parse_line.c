#include "minishell.h"

int
	parse_input(char *line, char ***line_split)
{

	if (!(*line_split = ft_split(line, ' '))) //Clement: use macro for ' '?
	{
		return (-1);
	}
	if (*line_split == NULL)	//Empty line, but may be useless considering we don't read unless we receive a \n from stdin??
	{
		printf("Empty line");
		return (0);
	}
	// + Check len and max arg here!
	// + Check if 1st arg of split is NULL
	/*
	** Check 1st arg:
	**	if built-in cmd: return BUILT_IN_CMD
	**	if local cmd (one we have to manage ourselves): return LOCAL_CMD
	**	else: set errno; return -1
	*/
	return (BUILT_IN_CMD);
}