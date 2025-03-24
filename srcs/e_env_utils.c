#include "../includes/minishell.h"

int	search_var_in_env(char **env, char *search)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(search, env[i], ft_strlen(search)) == 0
			&& (env[i][ft_strlen(search)] == '='
			|| env[i][ft_strlen(search)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*search_data_in_env(char **env, char *search)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(search);
	while (env[i])
	{
		if (ft_strncmp(search, env[i], size) == 0
			&& env[i][size] == '=')
			return (&env[i][size + 1]);
		i++;
	}
	return (NULL);
}

char	**add_var_in_env(char **env, char *data)
{
	char	**new_env;
	int		i;

	i = search_empty(env);
	if (i >= 0)
	{
		free_null((void **)&env[i]);
		env[i] = data;
		return (env);
	}
	i = 0;
	new_env = ft_calloc(ft_strslen(env) + 2, sizeof(char *));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = data;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	search_empty(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (env[i][0] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	**extract_paths(t_base *base)
{
	char	*env;
	char	**env_list;
	char	*env_listcpy;
	int		i;

	i = 0;
	env_list = NULL;
	env_listcpy = NULL;
	env = ft_strdup_protected(search_data_in_env(base->env, "PATH"));
	if (!env)
		return (NULL);
	env_list = ft_split(env, ':');
	if (!env_list)
		return (NULL);
	free_null((void **)&env);
	while (env_list[i])
	{
		env_listcpy = ft_strjoin(env_list[i], "/");
		if (!env_listcpy)
			return (free_doubletab(&env_list), NULL);
		free_null((void *)&env_list[i]);
		env_list[i] = env_listcpy;
		i++;
	}
	return (env_list);
}

/* void	erase_var(char **env, char *search)
{
	char	*to_erase;

	to_erase = search_var_in_env(env, search);
	if (to_erase)
	{
		free(to_erase);
		to_erase = ft_strdup("");
		if (!to_erase)
			write(2, "error strdup\n", 13);
	}
}
	char	**add_var_in_env(char **env, char *data)
{
	char	**new_env;
	int		i;

	i = search_empty(env);
	if (i >= 0)
	{
		env[i] = data;
		return (env);
	}
	else
	{
		i = 0;
		new_env = ft_calloc(ft_strslen(env) + 2, sizeof(char *));
		if (!new_env)
			exit(EXIT_FAILURE);
		while (env[i])
		{
			new_env[i] = env[i];
			i++;
		}
		new_env[i] = data;
		new_env[i + 1] = NULL;
		free_null((void **)env);
		return (new_env);
	}
} */