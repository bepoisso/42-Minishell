#include "../includes/minishell.h"

t_cmd	cmd_init(char **args, char **env)
{
	t_cmd	cmd;
	int		i;
	int		j;
	char	**res;

	j = 1;
	while (args[j][0] == '-')
		j++;
	res = (char **)malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (i <= j)
	{
		res[i] = ft_strdup(args[i]);
		i++;
	}
	cmd.env = env;
	return (cmd);
}

void	parser(char *str, char **env)
{
	char	**args;
	t_cmd	cmd;

	args = ft_split(str, ' ');
	cmd = cmd_init(args, env);
	check_args(args, env);
}
