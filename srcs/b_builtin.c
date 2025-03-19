
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
	return (0); // a retirer
}
