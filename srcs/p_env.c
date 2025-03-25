#include "../includes/minishell.h"

char	*search_env_var(char *search, char **env, t_base *base)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!search[i])
		return (ft_strdup("$"));
	if (search[i] == '?')
		return (ft_itoa(base->exit_code));
	while (env[i])
	{
		if (ft_strncmp(search, env[i], ft_strlen(search)) == 0)
		{
			j = ft_strlen(search);
			if (env[i][j] == '=')
				return (ft_strdup(env[i] + (j + 1)));
		}
		i++;
	}
	return (ft_strdup(""));
}
