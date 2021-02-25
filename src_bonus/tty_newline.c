/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_newline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:51:12 by jmaydew           #+#    #+#             */
/*   Updated: 2021/02/24 13:51:42 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int
	tty_newline(t_cursor *cursor)
{
	char *path;
	char *dir_name;

	path = getcwd(NULL, 0);
	write(STDIN_FILENO, "\x1b[1;31m", 7);
	write(1, SHELL_MSG, ft_strlen(SHELL_MSG));
	write(STDIN_FILENO, "\x1b[0m", 4);
	if (path && (dir_name = ft_strrchr(path, '/')))
	{
		dir_name++;
		write(STDIN_FILENO, "\x1b[1;34m", 7);
		write(STDIN_FILENO, " (", 2);
		write(1, dir_name, ft_strlen(dir_name));
		write(STDIN_FILENO, ") ", 2);
		write(STDIN_FILENO, "\x1b[0m", 4);
		free(path);
	}
	write(STDIN_FILENO, "\x1b[1;32m", 7);
	write(1, "$>", 2);
	write(STDIN_FILENO, "\x1b[0m", 4);
	if (tty_init_cursor(cursor) < 0)
		return (0);
}
