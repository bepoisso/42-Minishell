#include "../includes/minishell.h"

void	builtin_env(t_token *actual_tok)
{
	int		i;
	char	**env;

	(void)actual_tok;
	i = 0;
	env = actual_tok->base->env;
	while (env[i])
	{
		if (ft_strchr(env[i], (char)'='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	actual_tok->base->exit_code = 0;
}