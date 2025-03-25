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
	}
	return (1);
}

void	put_error(int type, char *name, t_base *base)
{
	if (type == 1)
	{
		ft_putstr_fd(RED"Minishell: exit: too many arguments\n"RESET, 2);
		base->exit_code = type;
	}
	if (type == 2)
	{
		ft_putstr_fd(RED"Minishell: exit: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": numeric argument required\n"RESET, 2);
		base->exit_code = type;
	}
}

void	proceed_exit(int exit_cde, t_base *base, t_cmd *cmd)
{
	if (cmd->next || cmd->prev)
		return ;
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
		if (!is_only_digit(actual->cmd->cmd[1]))
		{
			put_error(2, actual->cmd->cmd[1], actual->base);
			proceed_exit(2, actual->base, actual->cmd);
		}
		else
			put_error(1, "", actual->base);
	}
	else if (len == 2 && !is_only_digit(actual->cmd->cmd[1]))
	{
		put_error(2, actual->cmd->cmd[1], actual->base);
		proceed_exit(2, actual->base, actual->cmd);
	}
	else if (len == 2 && is_only_digit(actual->cmd->cmd[1]))
		proceed_exit(ft_atoi(actual->cmd->cmd[1]), actual->base, actual->cmd);
	else
		proceed_exit(actual->base->exit_code, actual->base, actual->cmd);
	return (actual->base->exit_code);
}
