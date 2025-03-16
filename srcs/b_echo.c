#include "../includes/minishell.h"

void	builtin_echo(t_token *actual_tok)
{
	int		i;
	char	**cmd;

	i = 1;
	cmd = actual_tok->cmd->cmd;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		if (cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	actual_tok->base->exit_code = 0;
}