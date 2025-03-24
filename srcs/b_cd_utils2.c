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
	ft_printf("%s\n", path);
	if (update_pwd(ft_strdup(path), base))
		return (ft_error("ERROR update_pwd", 1, base), 1);
	if (update_oldpwd(ft_strdup(backup), base))
		return (ft_error("ERROR update_oldpwd", 1, base), 1);
	return (0);
}
