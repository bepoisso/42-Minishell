#include "../includes/minishell.h"

char	*search_in_dualtab(char **tabstr, char *search)
{
	int	i;

	i = 0;
	while (tabstr[i])
	{
		if (!ft_strncmp(tabstr[i], search, ft_strlen(tabstr[i])))
			return(tabstr[i]);
		i++;
	}
	return (NULL);
}

static int	srch_n_destroy(t_token *tok, char *search)
{
	char	**envcpy;

	envcpy = tok->base->env;
	int	i;

	i = 0;
	while (envcpy[i])
	{
		if (!ft_strncmp(envcpy[i], search, ft_strlen(envcpy[i])))
			{
				free_null((void **)envcpy[i]);
				envcpy[i] = ft_strdup("");
				return (1);
			}
	}
	return (0);
}

static void	remove_node(t_var *to_remove)
{
	t_var	*prev;
	t_var	*next;

	prev = to_remove->prev;
	next = to_remove->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free_null((void **)&to_remove->content);
	free_null((void **)&to_remove->name);
	free_null((void **)&to_remove);			
	to_remove = to_remove->next;
}

/**
 * Possibilte de plusieurs variables a supprimer, fonction qui navigue dans la
 * liste d'arguments et supprime les noeuds qui sont dans la liste.
 * si aucun noeud trouve, il ne se passe rien
 */
void	builtin_unset(t_token *actual_tok)
{
	t_var	*act_var;
	int		i;

	i = 1;
	while (actual_tok->cmd->cmd[i])
	{
		if (!srch_n_destroy(actual_tok, actual_tok->cmd->cmd[i]))
		{
			act_var = search_in_var(actual_tok->base->envir, actual_tok->cmd->cmd[i]);
			if (act_var)
				remove_node(act_var);
		}
	}
}

