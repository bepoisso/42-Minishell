#include "../includes/minishell.h"

int	go_before(t_base *base)
{
	char	*path;
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	path = search_data_in_env(base->env, "OLDPWD");
	if (!path)
		return (ft_error("minishell: cd: OLDPWD not set", 1, base), 1);
	if (chdir(path) == -1)
		return (ft_error("ERROR chdir", 1, base), 1);
	update_oldpwd(backup, base);
	update_pwd(path, base);
	return (0);
}
