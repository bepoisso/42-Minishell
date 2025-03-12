#include "../includes/minishell.h"

int	get_redir_io(t_token *token)
{
	t_token *current;

	current = token;
	while (current)
	{
		if (ft_strncmp(current->data, "<<", 2) == 0)
			return (1);
		if (ft_strncmp(current->data, ">>", 2) == 0)
			return (2);
		if (ft_strncmp(current->data, "<", 1) == 0)
			return (1);
		if (ft_strncmp(current->data, ">", 1) == 0)
			return (2);
		current = current->prev;
	}
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
	if (ft_isspace(data[0]))
		return (0);
	return (-1);
}
