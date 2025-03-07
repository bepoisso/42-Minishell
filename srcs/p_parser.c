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
	t_token	*save;
	char	*temp;
	char	*temp2;
	char	*temp3;

	current = tokens;
	temp = NULL;
	temp2 = NULL;
	temp3 = NULL;
	while (current)
	{
		if (current->id == 11)
		{
			if (current->prev && current->next)
			{
				temp = ft_strdup(current->prev->data);
				free(current->prev->data);
				temp3 = ft_strndup(current->data + 1, ft_strlen(current->data) - 2);
				temp2 = ft_strjoin(temp, temp3);
				current->prev->data = ft_strjoin(temp2, current->next->data);
				current->id = 0;
				current->next->id = 0;
				free(temp);
				free(temp2);
				free(temp3);
			}
			else if (current->prev)
			{
				if (current->prev->id != 0)
				{
					temp = ft_strdup(current->prev->data);
					free(current->prev->data);
					temp3 = ft_strndup(current->data + 1, ft_strlen(current->data) - 2);
					current->prev->data = ft_strjoin(temp, temp3);
					current->id = 0;
					free(temp);
					free(temp3);
				}
			}
			else if (current->next)
			{
				if (current->next->id != 0)
				{
					temp = ft_strdup(current->next->data);
					free(current->next->data);
					temp3 = ft_strndup(current->data + 1, ft_strlen(current->data) - 2);
					current->next->data = ft_strjoin(temp3, temp);
					current->id = 0;
					free(temp);
					free(temp3);
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