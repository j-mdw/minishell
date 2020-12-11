/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 00:24:41 by jmaydew           #+#    #+#             */
/*   Updated: 2020/06/08 00:25:03 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# define BUFFER_SIZE 1024

int		get_next_line(int fd, char **line);
void	gnl_strcpy(char *dst, const char *src);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
int		gnl_strlen(const char *s);
int		ft_gnl(char **line, char *buffer);

#endif
