#include "../includes/minishell.h"

t_token	*create_token(char *value, bool literal)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = ft_strdup(value);
	new->literal = literal;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token(t_token **tokens, char *value, bool literal)
{
	t_token	*new;
	t_token	*temp;

	if (!value)
		return ;
	new = create_token(value, literal);
	if (!new)
		return;
	if (!*tokens)
		*tokens = new;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	free(value);
}

int	start_pipe(char *s, t_base *base)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
	i++;
	if (s[i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
			return (ft_error("minishell: syntax error near unexpected token `||'", 2, base), 1);
		else if (s[i] == '|')
			return (ft_error("minishell: syntax error near unexpected token `|'\n", 2, base), 1);
		else if (s[i] == '&' && s[i + 1] == '&')
			return (ft_error("minishell: syntax error near unexpected token `&&'", 2, base), 1);
		else if (s[i] == '&')
			return (ft_error("minishell: syntax error near unexpected token `&'\n", 2, base), 1);
		else if (s[i] == ':' || s[i] == '!')
			return (ft_error("minishell: syntax error near unexpected token `newline'", 2, base), 1);
	}
	return (0);
}

/**
 * tokenizer - Tokenizes a given string into a list of tokens.
 * @s: The input string to be tokenized.
 *
 * This function takes an input string and splits it into tokens based on
 * spaces, tabs, and quotes. It handles quoted substrings as single tokens.
 * The resulting tokens are stored in a linked list of t_token structures.
 *
 * Return: A pointer to the head of the linked list of tokens.
 */
t_token	*tokenizer(char *s, t_base *base)
{
	int		i;
	int		start;
	t_token	*tokens;
	bool	quote;
	bool	literal;

	i = 0;
	tokens = NULL;
	if (start_pipe(s, base))
		return (tokens);
	while (s[i])
	{
		literal = false;
		quote = false;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		start = i;
		if (s[i] == '"' || s[i] == '\'')
		{
			if (s[i] == '\'')
				literal = true;
			i = skip_quote(s, i) - 1;
			quote = true;
			start++;
		}
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '"' && s[i] != '\'')
				i++;
		}
		add_token(&tokens, ft_strndup(s + start, i - start), literal);
			i += (int)quote;
	}
	return (tokens);
}
