
#include "../includes/minishell.h"


char	*shlvl_modifier(char **environ, int i)
{
	int		j;
	char	*new_env;

	j = 0;
	new_env = ft_calloc(ft_strlen(environ[i]) + 2, sizeof(char));
	while (environ[i][j] && j < 6)
	{
		new_env[j] = environ[i][j];
		j++;
	}
	new_env[j] = environ[i][j] + 1;
	new_env[++j] = '\0';
	return (new_env);
}

char	**env_cpy(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	i = 0;
	new_env = ft_calloc((ft_strslen(environ) + 1), sizeof(char *));
	while (environ[i])
	{
		if(ft_strncmp(environ[i], "SHLVL", 5) == 0)
			new_env[i] = shlvl_modifier(environ, i);
		else
			new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/* char **env_cpy(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (ft_strslen(environ) + 1));
	while (environ[i])
	{
		if(ft_strncmp(environ[i], "SHLVL", 5) == 0)
			new_env[i] = shlvl_modifier(environ, i);
		else
			new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
} */