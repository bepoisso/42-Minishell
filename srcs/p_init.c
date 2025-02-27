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
		return (0);
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
	return (0);
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
		if (current->id >= 3 && current->id <= 6)
			redir = 1;
		if (!current->id)
		{
			if (redir == 1)
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
		else
			cmd = 0;
		current = current->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
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

void	chenechepa(t_base *base)
{
	// idenify_token()
	// create_cmd()

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
			count++;
		current = current->next;
	}
	base->count_pipe = count;
}
