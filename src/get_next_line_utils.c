/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 00:17:15 by jmaydew           #+#    #+#             */
/*   Updated: 2020/06/08 00:18:26 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
	{
		ptr = &((char *)s)[i];
		return (ptr);
	}
	else
		return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		str_len1;
	int		str_len2;
	int		i;
	char	*str;

	str_len1 = gnl_strlen(s1);
	str_len2 = gnl_strlen(s2);
	str = (char *)malloc(sizeof(char) * (str_len1 + str_len2 + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	gnl_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
