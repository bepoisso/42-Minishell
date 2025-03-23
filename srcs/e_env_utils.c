
#include "../includes/minishell.h"

int	search_var_in_env(char **env, char *search)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(search, env[i], ft_strlen(search)) == 0
			&& env[i][ft_strlen(search)] == '=')
			return (i);
		i++;
	}
	return (-1);
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
} */

char	*search_data_in_env(char **env, char *search)
{
	int	i;
	int size;

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

// char	**add_var_in_env(char **env, char *data)
// {
// 	char	**new_env;
// 	int		i;

// 	i = search_empty(env);
// 	if (i >= 0)
// 	{
// 		env[i] = data;
// 		return (env);
// 	}
// 	else
// 	{
// 		i = 0;
// 		new_env = ft_calloc(ft_strslen(env) + 2, sizeof(char *));
// 		if (!new_env)
// 			exit(EXIT_FAILURE);
// 		while (env[i])
// 		{
// 			new_env[i] = env[i];
// 			i++;
// 		}
// 		new_env[i] = data;
// 		new_env[i + 1] = NULL;
// 		free_null((void **)env);
// 		return (new_env);
// 	}
// }

char	**add_var_in_env(char **env, char *data)
{
	char	**new_env;
	int		i;

	i = search_empty(env);
	if (i >= 0)
	{
		env[i] = ft_strdup(data);
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
		env[i] = ft_strdup(data);
		new_env[i + 1] = NULL;
		free_null((void **)env);
		return (new_env);
	}
}

/**
 * recherche ligne vide
 * 
 */
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