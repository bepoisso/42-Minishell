#include "../includes/minishell.h"

char	*strnjoin(char *str, ...)
{
	char	*full_message;
	char	*va_tmp;
	char	*tmp;
	va_list	message_lst;

	full_message = NULL;
	va_tmp = NULL;
	tmp = NULL;
	va_start(message_lst, str);
	full_message = ft_strdup(str);
	if (!full_message)
		return (NULL);
	va_tmp = va_arg(message_lst, char *);
	while (va_tmp != NULL)
	{
		free_null((void **)&tmp);
		tmp = ft_strjoin(full_message, va_tmp);
		free_null((void **)&full_message);
		full_message = ft_strdup(tmp);
		va_tmp = va_arg(message_lst, char *);
	}
	free_null((void **)&tmp);
	va_end(message_lst);
	return (full_message);
}

int	cd_dot(t_base *base)
{
	char	backup[PATH_MAX];

	getcwd(backup, sizeof(backup));
	if (update_oldpwd(ft_strdup(backup), base))
		return (1);
	return (0);
}

int	update_pwd(char *new_data, t_base *base)
{
	int		i;
	char 	*data;

	data = NULL;
	i = search_var_in_env(base->env, "PWD");
	if (i >= 0)
	{
		free_null((void **)&base->env[i]);
		base->env[i] = ft_strjoin("PWD=",new_data);
		if (!base->env[i])
			return (1);
	}
	else
	{
		data = ft_strjoin("PWD=", new_data);
		base->env = add_var_in_env(base->env, data);
	}
	free_null((void **)&new_data);
	return (0);
}

int	update_oldpwd(char *new_data, t_base *base)
{
	int		i;
	char 	*data;

	data = NULL;
	i = search_var_in_env(base->env, "OLDPWD");
	if (i >= 0)
	{
		free_null((void **)&base->env[i]);
		base->env[i] = ft_strjoin("OLDPWD=",new_data);
		if (!base->env[i])
			return (1);
	}
	else
	{
		data = ft_strjoin("OLDPWD=", new_data);
		base->env = add_var_in_env(base->env, data);
	}
	free_null((void **)&new_data);
	return (0);
}

int	go_back(t_base *base)
{
	char	path[PATH_MAX];
	char	backup[PATH_MAX];

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
		return (ft_error("minishell: cd: No such file or directory", 1, base), 1);
	update_oldpwd(ft_strdup(backup), base);
	update_pwd(ft_strdup(path), base);
	return (0);
}
