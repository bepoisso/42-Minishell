#include "../includes/minishell.h"

int	parser(char *str, t_base *base)
{
	t_token	*tokens;

	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, base), 1);
	if (start_pipe(str, base))
		return (1);
	tokens = lexer(str, base);
	base->token = tokens;
	identify_token(base->token);
	base->token = token_parser(base->token);
	if (check_double_pippe(base->token)
			|| check_only_redirect(base->token, base))
		return (1);
	expanse(base->token, base->dollars);
	base->cmds = parsing_cmd(base);
	identify_builtin(base->cmds);
	return (0);
}

static void	join_quote(t_token *current)
{
	char	*temp;

	temp = ft_strdup(current->data);
	current->id = 11;
	current->literal = current->next->literal;
	free_null((void **)&current->data);
	current->data = ft_strjoin(temp, current->next->data);
	free(temp);
	rm_node_token(current->next);
}

static t_token	*remove_empty(t_token *current, t_token *tokens)
{
	t_token	*save;

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
			break ;
		current = save;
	}
	identify_token(tokens);
	rm_quote(tokens);
	identify_token(tokens);
	return (tokens);
}

t_token	*token_parser(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	handling_dollar(tokens, tokens->base);
	dollar_is_literal(tokens->base->dollars);
	while (current)
	{
		if (!ft_isop(current->data[0]) && current->id != 0)
		{
			if (current->next && (current->next->id == 11
					|| (current->id == 11 && !ft_isop(current->next->data[0])
						&& current->next->id != 0)))
			{
				join_quote(current);
				continue ;
			}
		}
		current = current->next;
	}
	current = tokens;
	tokens = remove_empty(current, tokens);
	return (tokens);
}
