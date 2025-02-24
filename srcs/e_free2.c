#include "../includes/minishell.h"

void	free_null(void	**ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_doubletab(char ***str)
{
	char	**temp;

	if (str && *str)
	{
		temp = *str;
		while (*temp)
		{
			free_null((void **)temp);
			temp++;
		}
		free_null((void **)str);
	}
}
