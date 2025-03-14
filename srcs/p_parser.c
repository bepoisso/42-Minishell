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

void	rm_quote(t_token *tokens)
{
	t_token	*current;
	char	*temp;
	int		i;
	int		j;

	current = tokens;
	while (current)
	{
		j = 0;
		i = -1;
		if (current && (ft_strchr(current->data, '\'') || ft_strchr(current->data, '"')))
		{
			temp = malloc(sizeof(char) * (ft_strlen(current->data) + 1));
			ft_memset(temp, 0, sizeof(char) * (ft_strlen(current->data) + 1));
			while (current->data[++i])
			{
				if (!(current->data[i] == '\'' || current->data[i] == '"'))
				{
					temp[j] = current->data[i];
					j++;
				}
			}
			free(current->data);
			current->data = ft_strdup(temp);
			free(temp);
		}
		current = current->next;
	}
}

t_token	*token_parser(t_token *tokens)
{
	t_token	*current;
	t_token	*save;
	char	*temp;

	current = tokens;
	temp = NULL;
	while (current)
	{
		if (!ft_isop(current->data[0]) && current->id != 0)
		{
			if (current->next && (current->next->id == 11 || (current->id == 11 && !ft_isop(current->next->data[0]) && current->next->id != 0)) )
			{
				temp = ft_strdup(current->data);
				current->id = 11;
				current->literal = current->next->literal;
				free(current->data);
				current->data = ft_strjoin(temp, current->next->data);
				rm_node_token(current->next);
				continue;
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
	identify_token(tokens);
	rm_quote(tokens);
	identify_token(tokens);
	return (tokens);
}

