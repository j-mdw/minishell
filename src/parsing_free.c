#include "minishell.h"

/*
** Free t_parse arrays if memory was allocated
** return 0
*/
int
	parsing_free(t_parse *parse_ptr)
{
	if (parse_ptr->control_op_split)
		ft_free_strarr(&(parse_ptr->control_op_split));
	if (parse_ptr->pipe_split)
		ft_free_strarr(&(parse_ptr->pipe_split));
	if (parse_ptr->cmd_split)
		ft_free_strarr(&(parse_ptr->cmd_split));
	return (0);
}