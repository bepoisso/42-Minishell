

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
 
int	sizeof_db_tab(char **array)
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

char	*search_in_env(char **env, char * search)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(search, env[i], ft_strlen(search))
			&& env[i][ft_strlen(search) == '='])
			return (&env[i][ft_strlen(search + 1)]);
		i++;
	}
	return (NULL);
}

/**
 * change_env_val a ecrire, modifi une variable existente
 */

/* fonction a ecrire qui va utiliser va args pour concatener autant de chaines
 que possible et renvoyer le resultat*/
char *make_err_mess()
{
	char *message;


	return (message);
}

static int	go_back(t_base *base, char *backup)
{
	if (chdir(search_in_env(base->env, "OLDPWD")) == -1)
		return (ft_error("minishell: cd: OLDPWD not set", 1, base));
	change_val_var(base->env, "OLDPWD", backup);
}


static int	go_home(t_base *base, char *backup)
{
	if (chdir(search_in_env(base->env, "HOME")) == -1)
		return (ft_error("minishell: cd: HOME not set", 1, base), 1);
	change_val_var(base->env, "OLDPWD", backup);
	return (0);
}

int	builtin_cd(t_token *actual_tok, t_base *base)
{
	char	backup[4096];
	char	*oldpwd_back;
	int		size;
	char	**envcpy;

	envcpy = actual_tok->base->env;
	size = sizeof_db_tab(actual_tok->cmd->cmd);
	if (size > 1)
	return (ft_error("Error minishell: cd: too many arguments\n", 2, base);
	getcwd(backup, sizeof(backup));
	if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "#", 2)))
	{
		if (go_home(base, backup))
			return (1);
	}
	else if (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "-", 2))
	{
		if (go_back(base, backup))
			return (1);
	}
	else
	{
		if (actual_tok->expanse.content[0] == '\0')
		{
			if (go_home(base, backup))
				return (1);
		}
		if (chdir(actual_tok->expanse.content) == -1)
			return (ft_error("chdir", 1, base);
		oldpwd_back = search_in_env(envcpy, "OLDPWD");
		if (!oldpwd_back)
			add_in_env(envcpy, backup, "OLDPWD");
	}
	return ;
}





/**
 * 
  */
/* void	builtin_cd(t_token *actual_tok)
{
	char	backup[4096];
	char	*oldpwd_back;
	int		size;
	t_var	*act_envir;

	size = sizeof_db_tab(actual_tok->cmd->cmd);
	getcwd(backup, sizeof(backup));
	if (size > 1)
		return (ft_error("Error minishell: cd: too many arguments\n", 2, actual_tok->base));
	if (size == 0 || (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "#", 2)))
	{
		if (chdir(search_in_env(actual_tok->base->env, "HOME")) == -1)
				return (ft_error("minishell: cd: HOME not set", 1, actual_tok->base));
		change_val_var(actual_tok->base->env, "OLDPWD", backup);
	}
	else if (size == 1 && ft_strncmp(actual_tok->cmd->cmd[0], "-", 2))
	{
		if (chdir(search_in_env(actual_tok->base->env, "OLDPWD")) == -1)
				return (ft_error("minishell: cd: OLDPWD not set", 1, actual_tok->base));
		change_val_var(actual_tok->base->env, "OLDPWD", backup);
	}
	else
	{
		if (actual_tok->expanse.content[0] == '\0')
			//GO HOME A ECRIRE;
		if (chdir(actual_tok->expanse.content) == -1)
			return (ft_error("chdir", 1, actual_tok->base));
		oldpwd_back = search_in_env(actual_tok->base->env, "OLDPWD");
		if (!oldpwd_back)
			add_in_env(actual_tok->base->env, backup, "OLDPWD");
	}
	return ;
} */

//fonction qui va chercher si une variable exite et renvoyer son adresse pour en recuperer le contenu ou la modifier
/* t_var	*search_in_var(t_var *env, char * search)
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
} */

/* void	builtin_cd(t_base *base, t_token *actual_tok)
{
	char	backup[4096];
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
} */