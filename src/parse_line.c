#include "minishell.h"

/*
** Split line on ';' then on '|'
** Sends the splited output to 'parse_pipe'
** Returns -1 on program error or Exit Status of 
** Returns 0 on success, -1 on error
*/

int
	parse_input(char *line, t_builtin *builtin_data)
{
	int		i;
	int		exit_status;
	char	**controlop_split;
	char	**pipe_split;
	// char	err_char;

	// if ((err_char = first_read(line)))
	// {
	// 	printf("minishell: parse error near \'%c\'", err_char);
	// 	return (1);
	// }
	if (!(controlop_split = ft_split(line, ';')))
		return (-1);
	i = 0;
	while (controlop_split[i])
	{
		if (!(pipe_split = ft_split(controlop_split[i], '|')))
		{
			ft_free_strarr(&controlop_split);
			return (-1);
		}
		// if (pipe_split[1])
		// {
			exit_status = exec_pipe(pipe_split, 0, STDIN_FILENO, builtin_data);
		// else
		// 	printf("Pass piped arg\n");
		ft_free_strarr(&(pipe_split));
		i++;
	}
	ft_free_strarr(&controlop_split);
	return (exit_status);
}