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

void	clean_exit(t_base *base)
{
	free_base(base);
	free_null((void **)&base->tild);
	free_doubletab(&base->env);
	rl_clear_history();
	exit (base->exit_code);
}
