/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 01:50:06 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 02:46:19 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_strncpy(char *dst, const char *const src, int len)
{
	int i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	**ft_split_init_array(char const *s, char c)
{
	int		i;
	int		count;
	char	**array;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
		return (NULL);
	array[count] = NULL;
	return (array);
}

static int	ft_mybs(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static void	*ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		j;
	int		ptr_ref;
	char	**array;

	ptr_ref = 0;
	if (s == NULL || (!(array = ft_split_init_array(s, c))))
		return (NULL);
	while (*s != '\0')
	{
		s += ft_mybs(s, c);
		j = 0;
		if (*s != c && *s != '\0')
		{
			while (s[j] != c && s[j] != '\0')
				j++;
			array[ptr_ref] = (char *)malloc(sizeof(char) * (j + 1));
			if (array[ptr_ref] == NULL)
				return (ft_free_array(array));
			array[ptr_ref] = ft_strncpy(array[ptr_ref], s, j);
			ptr_ref++;
			s += j;
		}
	}
	return (array);
}
