#include "../includes/minishell.h"

int	get_redir_io(t_token *token)
{
	t_token	*current;

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

int	get_op_token(char *data, int id)
{
	int	i;

	i = 0;
	if (!data || !*data)
		return (-2);
	if (ft_strncmp(data, "<<", 2) == 0 && id != 11)
		return (5);
	if (ft_strncmp(data, ">>", 2) == 0 && id != 11)
		return (6);
	if (ft_strncmp(data, "<", 1) == 0 && id != 11)
		return (3);
	if (ft_strncmp(data, ">", 1) == 0 && id != 11)
		return (4);
	if (ft_strncmp(data, "|", 1) == 0 && id != 11)
		return (7);
	if (ft_strncmp(data, "'", 1) == 0)
		return (11);
	if (ft_strncmp(data, "\"", 1) == 0)
		return (11);
	while (ft_isspace(data[i]))
		i++;
	if (!data[i])
		return (0);
	return (-1);
}

void	base_init(t_base *base)
{
	ft_memset(base, 0, sizeof(t_base));
	base->env = env_cpy();
	base->tild = ft_strdup(search_data_in_env(base->env, "HOME"));
	// header();
}
