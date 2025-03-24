#include "../includes/minishell.h"

int	builtin_exit(t_token *actual)
{
	int	len;

	len = ft_strslen(actual->cmd->cmd);
	ft_putstr_fd("exit", 1);
	if (len > 2)
	{
		ft_putstr_fd(RED"Minishell: exit: too many arguments"RESET, 2);
		write(2, "\n", 1);
		return (1);
	}
	if (actual->base->cmds->next || actual->base->cmds->prev)
		return (0);
	else if (len == 2)
	{
		actual->base->exit_code = ft_atoi(actual->cmd->cmd[1]);
		add_history(actual->base->input);
		clean_exit(actual->base);
	}
	else
	{
		add_history(actual->base->input);
		clean_exit(actual->base);
	}
	return (0);
}
