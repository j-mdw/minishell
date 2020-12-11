/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.ca>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:43:25 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 02:47:11 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_malloc_empty(void)
{
	char *str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		str_len;
	size_t	j;
	char	*substr;

	str_len = 0;
	if (s == NULL)
		return (NULL);
	while (s[str_len] != '\0')
		str_len++;
	if (str_len == 0 || ((unsigned int)str_len - 1) <= start || len == 0)
		return (ft_malloc_empty());
	else
	{
		substr = (char *)malloc(sizeof(char) * (len + 1));
		if (substr == NULL)
			return (NULL);
		j = 0;
		while (j < len && s[start + j] != '\0')
		{
			substr[j] = s[start + j];
			j++;
		}
		substr[j] = '\0';
	}
	return (substr);
}
