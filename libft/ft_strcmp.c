#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (!s1[i] && !s2[2])
		return (0);
	else
		return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
