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
 * 				1 : oldpwd = apply_expanse PWD
 * 				2 : pwd = new
 * 		if error :
 * 			Print: Error bash: cd: *new: No such file or directory RETURN
 */

static int	go_home(t_base *base, char *args)
{
	char	*path;
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(base->env, "HOME");
	if (args && (*args == '~'))
	{
		if (chdir(base->tild) == -1)
			return (ft_error("Minishell: cd: error cd: ~", 1, base), 1);
	}
	else if (chdir(path) == -1)
		return (ft_error("Minishell: cd: HOME not set", 1, base), 1);
	update_oldpwd(ft_strdup(backup), base);
	update_pwd(ft_strdup(path), base);
	return (0);
}

static int	go_root(t_base *base)
{
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	if (chdir("/") == -1)
		return (ft_error("Minishell: cd: error cd: /", 1, base), 1);
	update_oldpwd(ft_strdup(backup), base);
	update_pwd(ft_strdup("/"), base);
	return (0);
}

static int	go_there(t_base *base, t_cmd *act_cmd)
{
	char	backup[PATH_MAX];
	char	*path;
	char	*error;

	getcwd(backup, sizeof(backup));
	path = act_cmd->cmd[1];
	if (chdir(path) == -1)
	{
		error = ft_strnjoin("Minishell: cd: ", path,
				": No such file or directory", NULL);
		ft_error(error, 1, base);
		free_null((void **)&error);
		return (1);
	}
	update_oldpwd(ft_strdup(backup), base);
	update_pwd(ft_strdup(path), base);
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

int	builtin_cd(t_token *actual_tok, t_base *base)
{
	int		size;
	int		status;

	status = 0;
	if (actual_tok->base->cmds->next || actual_tok->base->cmds->prev)
		return (0);
	size = ft_strslen(actual_tok->cmd->cmd) - 1;
	if (size > 1)
		return (ft_error("Error Minishell: cd: too many arguments\n", 2,
				base), 1);
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
		status = go_there(base, actual_tok->cmd);
	return (status);
}
