

#include "../includes/minishell.h"


/**			CONSTRUCTION PLAN
 * 
 * for command :  cd new
 * 1 -> Backup pwd to change oldpwd inside env after all checks
 * 2 -> check nb of args :
 * 		if == 0 : Go to HOME
 * 		if == 1 : 
 * 			if new = -	: Go to oldpwd
 * 			if new = #	: GO to HOME
 * 			else 		: Go to New
 * 		if >=  2 : Error bash: cd: too many arguments RETURN
 * 
 * 3 -> Change pwd to New
 * 		if no error :
 * 			Update env:
 * 				1 : oldpwd = backup PWD
 * 				2 : pwd = new
 * 		if error :
 * 			Print: Error bash: cd: *new: No such file or directory RETURN
 * 
 */

/* int	check_args(char **args, t_base *base)
{

}

int	updt_env(char *new, t_base *base)
{

} */
 
static int	sizeof_db_tab(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}

//fonction qui va chercher si une variable exite et renvoyer son adresse pour en recuperer le contenu ou la modifier
t_var	*search_in_var(t_var *env, char * search)
{
	t_var	*act_env;

	act_env = env;
	while (act_env)
	{
		if (strncmp(search, act_env->name, ft_strlen(act_env->name)));
			return (act_env);
		act_env= act_env->next;
	}
	return (NULL);
}

/* fonction a ecrire qui va utiliser va args pour concatener autant de chaines
 que possible et renvoyer le resultat*/
char *make_err_mess()
{
	char *message;


	return (message);
}
/**
 * 
 * Gestion des messages d'erreur a faire
 * 
 */
void	builtin_cd(t_base *base, t_token *actual_tok)
{
	char	*backup;
	int		size;
	t_var	*act_envir;

	size = sizeof_db_tab(actual_tok->cmd->cmd);
	getcwd(backup, sizeof(backup));
	if (size > 1)
		return (ft_error("Error minishell: cd: too many arguments\n", 2, base));
	if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "#", 2)))
	{
		act_envir = search_in_var(base->envir, "HOME");
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: HOME not set", 1, base);	
	}
	else if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "-", 2)))
	{
		act_envir = search_in_var(base->envir, "OLDPWD");
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: OLDPWD not set", 1, base);	
	}
	else if (actual_tok->cmd->cmd[0][0] != '$')
	{
		if (chdir(actual_tok->cmd->cmd[0]) == -1)
			return (ft_error("chdir", 1, base));
		free (search_in_var(base->envir, "OLDPWD")->content);
		search_in_var(base->envir, "OLDPWD")->content = backup;
	}
	else if (actual_tok->cmd->cmd[0][0] == '$')
	{
		act_envir = search_in_var(base->envir, actual_tok->cmd->cmd[0]);
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: HOME not set", 1, base);	
	}
	return ;
}

/* void	builtin_cd(t_base *base, t_token *actual_tok)
{
	char	*backup;
	int		size;
	t_var	*act_envir;

	size = sizeof_db_tab(actual_tok->cmd->cmd);
	getcwd(backup, sizeof(backup));
	if (size > 1)
		return (ft_error("Error minishell: cd: too many arguments\n", 2, base));
	if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "#", 2)))
	{
		act_envir = search_in_var(base->env, "HOME");
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: HOME not set", 1, base);	
	}
	else if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "-", 2)))
	{
		act_envir = search_in_var(base->envir, "OLDPWD");
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: OLDPWD not set", 1, base);	
	}
	else if (actual_tok->cmd->cmd[0][0] != '$')
	{
		if (chdir(actual_tok->cmd->cmd[0]) == -1)
			return (ft_error("chdir", 1, base));
		free (search_in_var(base->envir, "OLDPWD")->content);
		search_in_var(base->envir, "OLDPWD")->content = backup;
	}
	else if (actual_tok->cmd->cmd[0][0] == '$')
	{
		act_envir = search_in_var(base->envir, actual_tok->cmd->cmd[0]);
		if (act_envir)
		{
			if (chdir(act_envir->content) == -1)
				return (ft_error("chdir", 1, base));
			search_in_var(base->envir, "OLDPWD")->content = backup;
		}
		else
			ft_error("minishell: cd: HOME not set", 1, base);	
	}
	return(0);
} */