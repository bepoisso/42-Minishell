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
	t_token *current;

	current = tokens;

	while (current)
	{
		// if (current->id == 11)
		current = current->next;
	}
	current = tokens;
	while (current)
	{
		if (current->id == 0)
			rm_node_token(current);
		current = current->next;
	}
	
	return (tokens);
}