#include "../includes/minishell.h"

int	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		return (1);
	}
}

void	put_error(int type, char *name)
{
	if (type == 1)
	{
		ft_putstr_fd(RED"Minishell: exit: too many arguments"RESET, 2);
		write(2, "\n", 2);
	}
	if (type == 2)
	{
		ft_putstr_fd(RED"Minishell: exit: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": numeric argument required", 2);
		write(2, RESET"\n", 2);
	}
}

void	proceed_exit(int exit_cde, t_base *base, t_cmd *cmd)
{
	if (cmd->next || cmd->prev)
		return (0);
	base->exit_code = exit_cde;
	ft_putstr_fd("exit\n", 2);
	add_history(base->input);
	clean_exit(base);
}

int	builtin_exit(t_token *actual)
{
	int	len;

	len = ft_strslen(actual->cmd->cmd);
	if (len > 2)
	{
		put_error(1, ""), actual->base->exit_code = 1;
		if (!is_only_digit(actual->cmd->cmd[1]))
			proceed_exit(1, actual->base, actual->cmd);
	}
	else if (len == 2 && !is_only_digit(actual->cmd->cmd[1]))
	{
		put_error(1, ""), actual->base->exit_code = 1;
		proceed_exit(1, actual->base, actual->cmd);
	}

	else if (len == 2 && is_only_digit(actual->cmd->cmd[1]))
		proceed_exit(ft_atoi(actual->cmd->cmd[1]), actual->base);
	else
		proceed_exit(actual->base->exit_code, actual->base);
	return (0);
}
