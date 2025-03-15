#include "../includes/minishell.h"

/* 	gestion des variable environnement
	dans le cas de env, penser a incrementer le compteur handle_env=X avec x
	 variable */
void	handle_env(t_cmd *cmd, t_token *act_tok, t_base *base, char **environ)
{
	char	*line;
	int		i;

	i = 0;
	while (environ[i])
	{
		printf("%s", environ[i]);
		i++;
	}
}

/* t_var*env_cpy(void)
{
	extern char	**environ;
	t_var		**new_env;
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