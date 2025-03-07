#include "../includes/minishell.h"

void	parser(char *str, t_base *base)
{
	t_token	*tokens;

	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, base));
	tokens = tokenizer(str, base);
	base->token = tokens;
}

t_token	*token_parser(t_token *tokens)
{
	t_token	*current;
	char	*temp;
	t_token	*save;

	current = tokens;
	temp = NULL;
	while (current)
	{
		if (current->id == 11)
		{
			if (current->prev)
			{
				if (current->prev->id != 0)
				{
					temp = ft_strdup(current->prev->data);
					free(current->prev->data);
					current->prev->data = ft_strjoin(temp, current->data);
					current->id = 0;
				}
			}
			if (current->next)
			{
				if (current->next->id != 0)
				{
					temp = ft_strdup(current->next->data);
					free(current->next->data);
					current->next->data = ft_strjoin(current->data, temp);
					current->id = 0;
				}
			}
		}
		current = current->next;
	}
	current = tokens;
	while (1)
	{
		save = current->next;
		if (current->id == 0)
		{
			if (current == tokens)
				tokens = tokens->next;
			rm_node_token(current);
		}
		if (save == NULL)
			break;
		current = save;
	}
	return (tokens);
}