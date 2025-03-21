
#include "../includes/minishell.h"

/****************************************************************
* 					What else to do :							*
* 																*
* cd:		TO FINISH	Zef	tester avec les $					*
* echo:		ToFix => gérer le -n								*
* pwd:		Do													*
* export:	ToDo												*
* unset:	Done zeph											*
* env:		Done Benja											*
* exit:		ToDo ne fait rien si pas seul fontion vide			*
* 																*
****************************************************************/

/**
 * MODIFIER FONCTIONS EN VOID EN INT POUR VERIFIER LE STATUS DE SORTIE
 * 
 */
int	exec_builtins(t_token *actual)
{
	int	status;

	status = 0;
	if (ft_strcmp(actual->data, "cd"))
		status = builtin_cd(actual, actual->base);
	else if (ft_strcmp(actual->data, "echo"))
		status = builtin_echo(actual->base, actual);
	else if (ft_strcmp(actual->data, "pwd"))
		status = builtin_pwd(actual->base);
	else if (ft_strcmp(actual->data, "export"))
		status = builtin_export(actual);
	else if (ft_strcmp(actual->data, "env"))
		status = builtin_env(actual);
	else if (ft_strcmp(actual->data, "unset"))
		status = builtin_unset(actual);
	return (status);
}
