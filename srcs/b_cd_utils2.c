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
