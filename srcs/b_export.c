/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:03:47 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/16 19:03:51 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* char	**add_in_env(char **env, char *data, char* name)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(sizeof_db_tab(env), sizeof(char *));
	while ()

} */


/**
 * 
 * 
 * export sans argument affiche env dans ordre acsii en utilisant strcmp et un bubble sort ou quicksort
 * export A ajoute une variable A vide en env
 * export A="plop" ajoute une variable contenant Plop
 * 
 */
void	builtin_export(t_token *actual_tok)
{
	(void)actual_tok;
}