
#include "../includes/minishell.h"

/**
 * unset doit etre la seule commande pour fonctionner
 * Fonction a tester
 * 
 * A modifier plus tard avec export, pas besoin de update_env, bash supprime la
 *  data mais garde la ligne du tableau pour l'utiliser apres avec export si
 * besoin
 * 
 */

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
		}
		i++;
	}
	return (erased);
}

int	update_env(t_token *tok, int size)
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
	free(tok->base->env);
	tok->base->env = envcpy;
	return (0);
}

/**
 * LESSCLOSE=/usr/bin/lesspipe non geree par minishell
 * LESSOPEN=| /usr/bin/lesspipe non geree par minishell
 * utlise par less, afficheur de texte que l'on utilise pas dans minishell
 * 
 */
int	builtin_unset(t_token *tok)
{
	int		i;
	int		erased;

	i = 1;
	erased = 0;
	if (tok->base->cmds->next != NULL)
		return (0);
	while (tok->cmd->cmd[i])
	{
		erased = srch_n_destroy(tok, tok->cmd->cmd[i]);
		if (erased == -1)
			return (1);
		i++;
	}
	/* if (erased)
	{
		if (update_env(tok, ft_strslen(tok->base->env) - erased + 1))
			return (1);
	} */
	return (0);
}
