#include "../includes/minishell.h"

int	count_forks(t_base *base)
{
	t_token	*tokcpy;

	tokcpy = base->token;
	while (tokcpy)
	{
		if (tokcpy->id == 9 && tokcpy->cmd->builtin == false)
			base->count_forks ++;
		tokcpy = tokcpy->next;
	}
	return (base->count_forks);
}

static void	put_err(int type, char *cmd)
{
	char	*err;

	err = NULL;
	if (type == 1)
		err = ft_strnjoin(RED"Command '", cmd,
				"' not found, but can be installed with:\nsudo apt install ",
				cmd, "\n"RESET, NULL);
	else if (type == 2)
		err = ft_strnjoin(RED"Minishell: ", cmd,
				": No such file or directory\n"RESET, NULL);
	else if (type == 3)
		err = ft_strnjoin(RED"Minishell: ", cmd,
				": Permission denied\n"RESET, NULL);
	ft_putstr_fd(err, 2);
	free_null((void **)&err);
}

static char	*is_absolute(t_token *actual, t_base *base)
{
	int	error;

	if (access(actual->cmd->cmd[0], X_OK) == 0)
		return (ft_strdup(actual->cmd->cmd[0]));
	error = errno;
	if (error == ENOENT)
	{
		put_err(2, actual->cmd->cmd[0]);
		base->exit_code = 127;
	}
	else if (error == EACCES)
	{
		put_err(3, actual->cmd->cmd[0]);
		base->exit_code = 126;
	}
	return (NULL);
}

static void	no_access(t_token *actual, t_base *base)
{
	base->exit_code = 126;
	put_err(3, actual->cmd->cmd[0]);
}

char	*check_cmd(t_token *actual, t_base *base)
{
	char	*path;
	char	**env_listcpy;

	if (ft_strchr(actual->cmd->cmd[0], '/'))
		return (is_absolute(actual, base));
	env_listcpy = base->path_list;
	path = NULL;
	if (!env_listcpy)
		return (base->exit_code = 127, put_err(2, actual->cmd->cmd[0]), NULL);
	while (*env_listcpy)
	{
		path = ft_strjoin(*env_listcpy, actual->cmd->cmd[0]);
		if (!path)
			return (ft_putstr_fd("Error strjoin", 2), NULL);
		if (access(path, X_OK) == 0)
			return (base->exit_code = 0, path);
		if (errno == EACCES)
			no_access(actual, base);
		free_null((void *)&path);
		env_listcpy++;
	}
	base->exit_code = 127;
	return (put_err(1, actual->cmd->cmd[0]), NULL);
}
