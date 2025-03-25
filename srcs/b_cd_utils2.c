#include "../includes/minishell.h"

int	go_before(t_base *base, t_cmd *act_cmd)
{
	char	*path;
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(base->env, "OLDPWD");
	if (!path)
		return (ft_error("minishell: cd: OLDPWD not set", 1, base), 1);
	if (act_cmd->next || act_cmd->prev)
		return (0);
	if (chdir(path) == -1)
		return (ft_error("ERROR chdir", 1, base), 1);
	ft_printf("%s\n", path);
	if (update_pwd(ft_strdup(path), base))
		return (ft_error("ERROR update_pwd", 1, base), 1);
	if (update_oldpwd(ft_strdup(backup), base))
		return (ft_error("ERROR update_oldpwd", 1, base), 1);
	return (0);
}

int	check_repertory(char *path, t_base *base)
{
	char	*error;

	if (access(path, F_OK) != 0)
	{
		error = ft_strnjoin(RED"Minishell: cd: ", path,
				": No such file or directory\n"RESET, NULL);
		ft_error(error, 1, base);
		free_null((void **)&error);
		return (1);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_error("minishell: cd : permission denied", 1, base);
		return (1);
	}
	return (0);
}

static void	handle_pwd(t_base *base, char *path, char *backup)
{
	update_oldpwd(ft_strdup(backup), base);
	if (path)
		update_pwd(ft_strdup(path), base);
	else
		update_pwd(ft_strdup(base->tild), base);
}

int	go_home(t_base *bs, t_cmd *act_cmd)
{
	char	*path;
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(bs->env, "HOME");
	if (act_cmd->next || act_cmd->prev)
	{
		if (!path && !act_cmd->cmd[1])
			ft_error(RED"Minishell: cd: HOME not set\n"RESET, 0, bs);
		return (0);
	}
	if (act_cmd->cmd[1] && (act_cmd->cmd[1][0] == '~'))
	{
		if (chdir(bs->tild) == -1)
			return (ft_error(RED"Minishell: cd: error cd~\n"RESET, 1, bs), 1);
	}
	else
	{
		if (!path)
			return (ft_error(RED"Minishell: cd: HOME no set\n"RESET, 1, bs), 1);
		if (chdir(path) == -1)
			return (ft_error(RED"error: chdir cd HOME\n"RESET, 1, bs), 1);
	}
	handle_pwd(bs, path, backup);
	return (0);
}
