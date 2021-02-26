/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:13:03 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/26 14:46:13 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Open and create a file if necessary, in TRUNC or append mode
** depending on '>' vs '>>'
** returns the fd of the file opened
** overwrites the filename and redir symbols with whitespaces
*/

static int
	parse_output_redir(char *line, t_list *local_env)
{
	int		i;
	int		append_flag;
	int		fd;
	char	*filename;

	i = 0;
	line[i++] = ' ';
	append_flag = O_TRUNC;
	if (line[i] == '>' && (append_flag = O_APPEND))
		line[i++] = ' ';
	if (!(filename = get_filename(&(line[i]), local_env)))
		return (-1);
	if ((fd = open(filename, O_RDWR | O_CREAT | append_flag, 0664)) < 0)
	{
		free(filename);
		return (-1);
	}
	free(filename);
	return (fd);
}

/*
** Find filename and Open the correcponding file if it exists
** returns the fd of the file opened or -1 if it doesn't exist
** overwrites the filename and redir symbols with whitespaces
*/

static int
	parse_input_redir(char *line, t_list *local_env)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	line[i] = ' ';
	i++;
	if (!(filename = get_filename(&(line[i]), local_env)))
		return (-1);
	if ((fd = open(filename, O_RDWR, 0664)) < 0)
	{
		free(filename);
		return (-1);
	}
	free(filename);
	return (fd);
}

static int
	parse_redir_out(char *line, int i, t_list *local_env, int redirfd[2])
{
	if (redirfd[0] != STDIN_FILENO)
		close(redirfd[0]);
	if ((redirfd[0] = parse_input_redir(&(line[i]), local_env)) < 0)
	{
		printf("Error: %s\n", strerror(errno));
		ft_memset(line, ' ', ft_strlen(line));
		return (close_if(redirfd[1], STDOUT_FILENO) - 1);
	}
	return (0);
}

/*
** Search for redirection symbols in *line
** Open/Create redirection files if they don't exist
** Replaces redirections char and filenames in *line with blank spaces
*/

int
	parse_redirections(char *line, int redirfd[2], t_lit_status *lit_status, \
	t_list *local_env)
{
	int	i;

	i = 0;
	redirfd[0] = STDIN_FILENO;
	redirfd[1] = STDOUT_FILENO;
	while (line[i] && !is_lit(line[i], lit_status))
	{
		if (line[i] == '>')
		{
			if (redirfd[1] != STDOUT_FILENO)
				close(redirfd[1]);
			if ((redirfd[1] = parse_output_redir(&(line[i]), local_env)) < 0)
			{
				printf("Error: %s\n", strerror(errno));
				return (close_if(redirfd[0], STDIN_FILENO) - 1);
			}
		}
		else if (line[i] == '<' && \
		(parse_redir_out(line, i, local_env, redirfd) < 0))
			return (-1);
		i++;
	}
	return (0);
}
