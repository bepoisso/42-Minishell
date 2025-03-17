/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:01:34 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/17 10:59:30 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (strncmp(search, tok->base->env[i], ft_strlen(search))
			&& tok->base->env[i][ft_strlen(search) == '='])
		{
			free_null((void **)&tok->base->env[i]);
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
	envcpy = ft_calloc(sizeof_db_tab(env), sizeof(char **) * size);
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
	if (erased)
	{
		if (update_env(tok, sizeof_db_tab(tok->base->env) - erased + 1))
			return (1);
	}
	return (0);
}

/* static void	remove_node(t_var *to_remove)
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
} */
/**
 * Possibilte de plusieurs variables a supprimer, fonction qui navigue dans la
 * liste d'arguments et supprime les noeuds qui sont dans la liste.
 * si aucun noeud trouve, il ne se passe rien
 */
/* int	builtin_unset(t_token *actual_tok)
{
	t_var	*act_var;
	int		i;

	i = 1;
	if (actual_tok->base->cmds->next != NULL)
		return (0);
	while (actual_tok->cmd->cmd[i])
	{
		if (srch_n_destroy(actual_tok, actual_tok->cmd->cmd[i]))
		{
			act_var = search_in_var(actual_tok->base->envir
				, actual_tok->cmd->cmd[i]);
			if (act_var)
				remove_node(act_var);
		}
	}
} */