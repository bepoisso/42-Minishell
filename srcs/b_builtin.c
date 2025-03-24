#include "../includes/minishell.h"

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
	else if (ft_strcmp(actual->data, "exit"))
		status = builtin_exit(actual);
	return (status);
}
