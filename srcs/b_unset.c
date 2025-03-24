#include "../includes/minishell.h"

static int	srch_n_destroy(t_token *tok, char *search)
{
	int		i;
	int		erased;

	erased = 0;
	i = 0;
	while (tok->base->env[i])
	{
		if (!ft_strncmp(search, tok->base->env[i], ft_strlen(search))
			&& tok->base->env[i][ft_strlen(search) == '='])
		{
			free_null((void **)&tok->base->env[i]);
			tok->base->env[i] = ft_strdup("");
			erased++;
			return (erased);
		}
		i++;
	}
	return (erased);
}

/* int	update_env(t_token *tok, int size)
{
	int		i;
	int		j;
	char	**env;
	char	**envcpy;

	i = 0;
	j = 0;
	env = tok->base->env;
	envcpy = ft_calloc(ft_strslen(env), sizeof(char **) * size);
	if (!envcpy)
		return (1);
	while (env[i])
	{
		while (env[i])
		{
			if (!env[i])
				i++;
			else
			{
				envcpy[j] = env[i];
				j++;
				i++;
			}
		}
	}
	free_null((void **)&tok->base->env);
	tok->base->env = envcpy;
	return (0);
} */

int	builtin_unset(t_token *tok)
{
	int		i;
	int		erased;

	i = 1;
	erased = 0;
	if (tok->base->cmds->next || tok->base->cmds->prev)
		return (0);
	while (tok->cmd->cmd[i])
	{
		erased = srch_n_destroy(tok, tok->cmd->cmd[i]);
		if (erased == -1)
			return (1);
		i++;
	}
	return (0);
}
