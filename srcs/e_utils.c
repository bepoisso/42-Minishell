
#include "../includes/minishell.h"

int ft_strslen(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			i++;
	}
	return (i);
}