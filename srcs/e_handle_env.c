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
