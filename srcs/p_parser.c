#include "../includes/minishell.h"

int	parser(char *str, t_base *base)
{
	t_token	*tokens;

	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, base), 1);
	tokens = tokenizer(str, base);
	base->token = tokens;
	return (0);
}

t_token	*token_parser(t_token *tokens)
{
	t_token	*current;
	t_token	*save;
	char	*temp;
	char	*temp2;
	char	*temp3;
	
	while (1)
	{
		current = tokens;
		temp = NULL;
		temp2 = NULL;
		temp3 = NULL;
		while (current)
		{
			if (current->id == 11)
			{
				if (current->prev && current->next && current->prev->id != 0 && current->next->id != 0 && !ft_isop(current->prev->data[0]) && !ft_isop(current->next->data[0]))
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
				else if (current->prev && current->prev->id != 0 && !ft_isop(current->prev->data[0]))
				{
					temp = ft_strdup(current->prev->data);
					free(current->prev->data);
					temp3 = ft_strndup(current->data + 1, ft_strlen(current->data) - 2);
					current->prev->data = ft_strjoin(temp, temp3);
					current->id = 0;
					free(temp);
					free(temp3);
				}
				else if (current->next && current->next->id != 0 && !ft_isop(current->next->data[0]))
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
			current = current->next;
		}
		current = tokens;
		while (1)
		{
			if (!current)
				break ;
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
		if (no_quote(tokens) == 0)
			break;
	}
	return (tokens);
}
