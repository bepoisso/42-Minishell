/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:59:31 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/18 19:33:25 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 */

 int	cd_dot(t_base *base)
 {
	int		i;
	char	backup[4096];

	getcwd(backup, sizeof(backup));
 
	i = search_var_in_env(base->env, "OLDPWD");
	if (i >= 0)
	{
		free_null((void **)&base->env[i]);
		base->env[i] = ft_strjoin("OLDPWD=",backup);
		return (0);
	}
	else
	{
		base->env = add_var_in_env(base->env, backup);
	}
	return (0);
 }

static int	update_oldpwd(char *new_data, t_base *base)
{
	int		i;

	i = search_var_in_env(base->env, "OLDPWD");
	if (i >= 0)
	{
		free_null((void **)&base->env[i]);
		base->env[i] = ft_strjoin("OLDPWD=",new_data);
		return (0);
	}
	else
	{
		base->env = add_var_in_env(base->env, new_data);
	}
	return (0);
}

/* fonction a ecrire qui va utiliser va args pour concatener autant de chaines
 que possible et renvoyer le resultat*/
/* char *make_err_mess()
{
	char *message;

	return (message);
} */
/**
 * @attention A message d'erreur a ecrire 
 */
static int	go_back(t_base *base)
{
	char	path[4096];
	char	backup[4096];

	int		i;
	getcwd(path, sizeof(path));
	getcwd(backup, sizeof(backup));
	if (!path[0])
		return (1);
	i = ft_strlen(path) - 1;
	while (i >= 0 && path[i] != '/')
		i--;
	path[i + 1] = '\0';
	if (chdir(path) == -1)
		return (ft_error("minishell: cd: OLDPWD not set", 1, base), 1);
	update_oldpwd(backup, base);
	return (0);
}

static int	go_before(t_base *base)
{
	char	*path;
	char	backup[4096];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(base->env, "OLDPWD");
	if (!path)
		return (ft_error("minishell: cd: OLDPWD not set", 1, base), 1);
	if (chdir(path) == -1)
		return (ft_error("ERROR chdir", 1, base), 1);
	update_oldpwd(backup, base);
	return (0);
}

static int	go_home(t_base *base, char *args)
{
	char	*path;
	char	backup[4096];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(base->env, "HOME");
	if (args && ( *args == '~'))
	{
		if (chdir(base->tild) == -1)
			return (ft_error("minishell: cd: error cd: ~", 1, base), 1);
	}
	else if (chdir(path) == -1)
		return (ft_error("minishell: cd: HOME not set", 1, base), 1);
	update_oldpwd(backup, base);
	return (0);
}

static int	go_root(t_base *base)
{
	char	backup[4096];

	getcwd(backup, sizeof(backup));
	if (chdir("/") == -1)
		return (ft_error("minishell: cd: error cd: /", 1, base), 1);
	update_oldpwd(backup, base);
	return (0);
}

/**
 * erreur a ecrire
 */
static int	go_there(t_base *base, t_token *act_tok)
{
	char	backup[4096];
	char	*path;

	getcwd(backup, sizeof(backup));
	if (act_tok->expanse.content)
		path = act_tok->expanse.content;
	else if (!act_tok->expanse.content)
		path = act_tok->cmd->cmd[1];
	if (chdir(path) == -1)
	return (ft_error("chdir", 1, base), 1);
	update_oldpwd(backup, base);
	return (0);
}

static int	is_home(char *path)
{
	if (!ft_strncmp(path, "#", 2))
		return (1);
	else if (!ft_strncmp(path, "~", 2))
		return (1);
	else if (path[0] == '\0')
		return (1);
	else
		return (0);
}
/**
 * gere cd . qui remplace le oldpwd par la position actuelle sans changer de dossier
 * 
 * 
 */
int	builtin_cd(t_token *actual_tok, t_base *base)
{
	int		size;
	int		status;

	status = 0;
	size = ft_strslen(actual_tok->cmd->cmd) - 1;
	if (size > 1)
		return (ft_error("Error minishell: cd: too many arguments\n", 2, base), 1);
	else if (size == 0 || (size == 1 && is_home(actual_tok->cmd->cmd[1])))
		status = go_home(base, actual_tok->cmd->cmd[1]);
	else if ((size == 1 && !ft_strncmp(actual_tok->cmd->cmd[1], "/", 2)))
		status = go_root(base);
	else if (size == 1 && !ft_strncmp(actual_tok->cmd->cmd[1], "-", 2))
		status = go_before(base);
	else if (size == 1 && !ft_strncmp(actual_tok->cmd->cmd[1], ".", 2))
		status = cd_dot(base);
	else if (size == 1 && !ft_strncmp(actual_tok->cmd->cmd[1], "..", 2))
		status = go_back(base);
	else
		status = go_there(base, actual_tok);
	return (status);
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

	size = ft_strslen(actual_tok->cmd->cmd);
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
		if (ft_strncmp(search, act_env->name, ft_strlen(act_env->name)));
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

	size = ft_strslen(actual_tok->cmd->cmd);
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