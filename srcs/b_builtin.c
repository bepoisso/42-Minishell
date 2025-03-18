/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:34:12 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/18 13:10:29 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/minishell.h"

/****************************************************************
* 					What else to do :							*
* 																*
* cd:		TO FINISH	Zef										*
* echo:		ToFix => gérer le -n								*
* pwd:		Do													*
* export:	ToDo												*
* unset:	ToDo												*
* env:		ToFix => ordre alphabétique ! = Bash				*
* exec:		ToDo ne fait rien si pas seul						*
* 																*
****************************************************************/

/**
 * MODIFIER FONCTIONS EN VOID EN INT POUR VERIFIER LE STATUS DE SORTIE
 * 
 */
void	exec_builtins(t_token *actual)
{
	/* int	status;

	status = 0; */
	if (ft_strcmp(actual->data, "echo"))
		builtin_echo(actual);
	else if (ft_strcmp(actual->data, "cd"))
		builtin_cd(actual, actual->base);
	else if (ft_strcmp(actual->data, "pwd"))
		builtin_pwd(actual->base);
	else if (ft_strcmp(actual->data, "export"))
		builtin_export(actual);
	else if (ft_strcmp(actual->data, "env"))
		builtin_env(actual);
	else if (ft_strcmp(actual->data, "unset"))
		builtin_unset(actual);
	// else if (ft_strcmp(actual->data, "exit"))

	// return (status);
}
