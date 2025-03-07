#include "../includes/minishell.h"

int	get_redir_io(char *data)
{
	if (ft_strncmp(data, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(data, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(data, "<", 1) == 0)
		return (1);
	if (ft_strncmp(data, ">", 1) == 0)
		return (2);
	return (0);
}

int	get_op_token(char *data)
{
	if (!data || !*data)
		return (-2);
	if (ft_strncmp(data, "<<", 2) == 0)
		return (5);
	if (ft_strncmp(data, ">>", 2) == 0)
		return (6);
	if (ft_strncmp(data, "<", 1) == 0)
		return (3);
	if (ft_strncmp(data, ">", 1) == 0)
		return (4);
	if (ft_strncmp(data, "|", 1) == 0)
		return (7);
	if (ft_strncmp(data, "'", 1) == 0)
		return (11);
	if (ft_strncmp(data, "\"", 1) == 0)
		return (11);
	if (ft_isspace(*data))
		return (0);
	return (-1);
}

void	identify_token(t_base *base)
{
	t_token	*current;
	int		cmd;
	int		redir;

	cmd = 0;
	redir = 0;
	current = base->token;
	while (current)
	{
		current->id = get_op_token(current->data);
		if ((current->id >= 3 && current->id <= 6))
			redir = 1;
		if (current->id >= 1 && current->id <= 7)
			cmd = 0;
		if (current->id == -1)
		{
			if (redir == 1 && current->id != 0)
			{
				current->id = get_redir_io(current->prev->data);
				redir = 0;
			}
			else if (cmd == 0)
			{
				current->id = 9;
				cmd = 1;
			}
			else
				current->id = 10;
		}
		current = current->next;
	}
}

void	identify_builtin(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (ft_strcmp("echo", current->cmd[0])
			|| ft_strcmp("cd", current->cmd[0])
			|| ft_strcmp("pwd", current->cmd[0])
			|| ft_strcmp("export", current->cmd[0])
			|| ft_strcmp("unset", current->cmd[0])
			|| ft_strcmp("env", current->cmd[0])
			|| ft_strcmp("exit", current->cmd[0]))
			current->builtin = true;
		else
			current->builtin = false;
		current = current->next;
	}
}

void	pipe_counter(t_base *base)
{
	int		count;
	t_token	*current;

	count = 0;
	current = base->token;
	while (current)
	{
		if (current->id == 7)
		{
			count++;
			current->index_pipe = count;
		}
		current = current->next;
	}
	base->count_pipe = count;
}
