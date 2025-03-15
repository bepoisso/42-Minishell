

#include "../includes/minishell.h"

/****************************************************************
* 					What else to do :							*
* 																*
* cd:		TO FINISH	Zef											*
* echo:		ToFix => gérer le -n								*
* pwd:		Do													*
* export:	ToDo												*
* unset:	ToDo												*
* env:		ToFix => ordre alphabétique ! = Bash				*
* exec:		ToDo ne fait rien si pas seul						*
* 																*
****************************************************************/
/* void	handling_builtin(t_base *base, t_token *actual_tok)
{
	base->env = env_cpy();
	if (ft_strncmp(actual_tok->data, "echo", 5) == 0)
		builtin_echo(base, actual_tok);
	else if (ft_strncmp(actual_tok->data, "pwd", 4) == 0)
		builtin_pwd(base);
	else if (ft_strncmp(actual_tok->data, "env", 4) == 0)
		builtin_env(base, actual_tok);
		// else if (ft_strncmp(actual_tok->data, "cd", 3))
		// 	builtin_cd(base, actual_tok);
		// if (ft_strncmp(actual_tok->data, "export", 7))
		// 	builtin_export(base, actual_tok);
		// if (ft_strncmp(actual_tok->data, "unset", 6))
		// 	builtin_unset(base, actual_tok);
} */

/**
 * MODIFIER FONCTIONS EN VOID EN INT POUR VERIFIER LE STATUS DE SORTIE
 * 
 */
void	exec_builtins(t_token *actual, t_base *base)
{
	//int	status;

	//status = 0;
	if (ft_strcmp(actual->data, "echo"))
		builtin_echo(base, actual);
	else if (ft_strcmp(actual->data, "cd"))
		builtin_cd(base, actual);
	else if (ft_strcmp(actual->data, "pwd"))
		builtin_pwd(base);
	else if (ft_strcmp(actual->data, "export"))
		builtin_export(base, actual);
	else if (ft_strcmp(actual->data, "env"))
		builtin_env(base, actual);
/* 	else if (ft_strcmp(actual->data, "exit"))
		builtin_exit(base); */
	//return (status);
}

int ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

// TEMP SERT A QUOI?
char	*shlvl_modifier(char **environ, int i)
{
	int		j;
	int		temp;
	char	*new_env;

	j = 0;
	temp = ft_atoi(environ[i] + 6) + 1;
	new_env = ft_calloc(ft_strlen(environ[i]) + 2, sizeof(char));
	while (environ[i][j] && j < 6)
	{
		new_env[j] = environ[i][j];
		j++;
	}
	new_env[j] = environ[i][j] + 1;
	new_env[++j] = '\0';
	return (new_env);
}

char **env_cpy(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (ft_strslen(environ) + 1));
	while (environ[i])
	{
		if(ft_strncmp(environ[i], "SHLVL", 5) == 0)
			new_env[i] = shlvl_modifier(environ, i);
		else
			new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

