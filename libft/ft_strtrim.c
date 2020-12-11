/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 01:19:48 by jmaydew           #+#    #+#             */
/*   Updated: 2020/05/19 02:49:20 by jmaydew          ###   ########.fr       */
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

static int	ft_trim_beg_index(char const *s1, char const *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (set[i] != '\0')
	{
		if (s1[j] == set[i])
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
	return (j);
}

static int	ft_trim_end_index(char const *s1, char const *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
		j++;
	if (j == 0)
		return (0);
	else
		j -= 1;
	while (set[i] != '\0')
	{
		if (s1[j] == set[i])
		{
			j--;
			i = 0;
		}
		else
			i++;
	}
	return (j);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		h;
	int		i;
	int		j;
	char	*str;

	h = ft_trim_beg_index(s1, set);
	j = ft_trim_end_index(s1, set);
	if (h > j)
		return (ft_malloc_empty());
	str = (char *)malloc(sizeof(char) * (j - h + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < (j - h + 1))
	{
		str[i] = s1[h + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
