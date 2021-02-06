/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clkuznie <clkuznie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:27:53 by clkuznie          #+#    #+#             */
/*   Updated: 2021/01/29 16:27:54 by clkuznie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct  s_lit_status {
        int             quote;
        int             dquote;
        int             backs;
}               t_lit_status;

t_lit_status lit_status;


static int  is_lit(char c)
{
    if (!lit_status.quote && !lit_status.dquote && !lit_status.backs)
    {
        lit_status.quote = (c == '\'');
        lit_status.dquote = (c == '\"');
        lit_status.backs = (c == '\\');
        return (0);
    }
    lit_status.quote -= ((c == '\'') && lit_status.quote);
    lit_status.dquote -= ((c == '\"') && lit_status.dquote);
    lit_status.backs = 0;
    return (1); 
}

static int	count_strs(char const *s, char c)
{
	int		i;
	int		s_nbr;

	i = 0;
	s_nbr = 0;
	if (!c)
		return ((s[i]) ? s_nbr + 1 : s_nbr);
	while (s[i])
	{
		if (is_lit(s[i]) || s[i] != c)
		{
			++s_nbr;
            ++i;
			while (s[i] && (is_lit(s[i]) || s[i] != c))
				++i;
			continue ;
		}
		++i;
	}
	return (s_nbr);
}

static void	clean_mem(char ***strs)
{
	int		i;

	i = 0;
	while ((*strs)[i])
	{
		free((*strs)[i]);
		++i;
	}
	free(*strs);
	*strs = NULL;
}

static int	duplicate(char const *s, char c, char **strs, int s_nbr)
{
	int		i;
	int		j;

	i = 0;
	while (i < s_nbr)
	{
		j = 0;
        while (!is_lit(s[j]) && s[j] == c)
			++j;
		s += j;
		j = 0;
		while (s[j] && (is_lit(s[j]) || s[j] != c))
			++j;
		if (!(strs[i] = ft_strndup(s, j)))
			return (0);
		s += j;
		++i;
	}
	return (1);
}

char		**
	shell_split(char const *s, char c)
{
	char	**strs;
	int		s_nbr;

lit_status.quote = 0;
lit_status.dquote = 0;
lit_status.backs = 0;
	if (s)
		s_nbr = count_strs(s, c);
	if (!(strs = malloc((s_nbr + 1) * sizeof(s))))
		return (NULL);
	strs[s_nbr] = NULL;
	if (!duplicate(s, c, strs, s_nbr))
		clean_mem(&strs);
	return (strs);
}

void
	free_strarr(char ***strarr)
{
	int	i;

	i = 0;
	while ((*strarr)[i])
	{
		free((*strarr)[i]);
		i++;
	}
	free(*strarr);
	*strarr = NULL;
}

void
    ft_putstrarr(char **arr)
{
    int i;

    if (arr)
    {
        i = 0;
        while (arr[i])
        {
            ft_putstr_fd(arr[i], STDOUT_FILENO);
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
    char line[1000];
    char **arr;
    bzero(line, 1000);
    while (scanf("%[^\n]s", line))
    {
        arr = shell_split(line, ';');
        // write (1, "toto\n", 5);
        ft_putstrarr(arr);
        free_strarr(&arr);
        int i = 0;
        while (line[i])
        {
            int tto = is_lit(line[i]);
            printf("%i", tto);
            i++;
        }
        bzero(line, 1000);
    }
    return 0;
}

// unset HOME & cd
// mkdir test; cd test; rm -rf ../rf
// env -i ./minishell000
