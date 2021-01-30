/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 00:05:38 by jmaydew           #+#    #+#             */
/*   Updated: 2021/01/30 11:03:46 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gnl(char **line, char *buffer)
{
	char *ptr;
	char *new_line;

	if ((ptr = ft_strchr(buffer, '\n')) != NULL)
	{
		*ptr = '\0';
		new_line = ft_strjoin(*line, buffer);
		free(*line);
		*line = new_line;
		ft_strcpy(buffer, ptr + 1);
		return (1);
	}
	else
	{
		new_line = ft_strjoin(*line, buffer);
		free(*line);
		*line = new_line;
		buffer[0] = '\0';
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	int			bytes_read;
	static char	buffer[BUFFER_SIZE + 1];

	if (!line || BUFFER_SIZE == 0 || fd < 0)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	*line[0] = '\0';
	while (1)
	{
		if (buffer[0] == '\0')
		{
			if ((bytes_read = read(fd, buffer, BUFFER_SIZE)) < 0)
				return (-1);
			if (bytes_read == 0 && !(*line)[0])
				return (0);
			buffer[bytes_read] = '\0';
		}
		if (ft_gnl(line, buffer) == 1)
			return (1);
	}
}
