#include "../includes/minishell.h"

int	bypass_args(char *arg)
{
	int		j;

	j = 0;
	if (arg[j] && ft_strncmp(arg , "-n", 2) == 0)
	{
		j = 1;
		while (arg[j] == 'n')
		j++;
		if (arg[j] == '\0')
			return (true);
	}
	return (false);
}

int	builtin_echo(t_base *base, t_token *actual_tok)
{
	int		i;
	char	**cmd;
	bool	line_return;
	bool	printing;

	i = 1;
	printing = false;
	cmd = actual_tok->cmd->cmd;
	while (cmd[i])
	{
		if (printing == false && bypass_args(cmd[i]) == true)
		{
			line_return = false;
			i++;
			continue;
		}
		ft_putstr(cmd[i]);
		printing = true;
		if (cmd[i + 1])
			ft_putchar(' ');
		i++; 
	}
	if (line_return)
		ft_putchar('\n');
	base->exit_code = 0;
	return (0);
}
