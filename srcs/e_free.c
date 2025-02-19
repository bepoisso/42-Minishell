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

void	free_n_tabint(int **tabint, int n)
{
	while (n > 0)
	{
		n--;
		free_null((void **)&tabint[n]);
	}
	free(tabint);
}

//A FAIRE
void	free_exec(t_base *base)
{
	
}
