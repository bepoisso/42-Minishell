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

void	chenechepa(t_base *base)
{
	// idenify_token()
	// create_cmd()

}
