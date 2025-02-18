#include "../includes/minishell.h"

t_token	*create_token(char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token(t_token **tokens, char *value)
{
	t_token	*new;
	t_token	*temp;

	if (!value)
		return ;
	new = create_token(value);
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
t_token	*tokenizer(char *s)
{
	int		i;
	int		start;
	t_token	*tokens;
	bool	quote;

	i = 0;
	tokens = NULL;
	while (s[i])
	{
		quote = false;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		start = i;
		if (s[i] == '"' || s[i] == '\'')
		{
			i = skip_quote(s, i) - 1;
			quote = true;
			start++;
		}
		else
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '"' && s[i] != '\'')
				i++;
		add_token(&tokens, ft_strndup(s + start, i - start));
			i += (int)quote;
	}
	return (tokens);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%d] [%s]\n", tokens->id, tokens->data);
		tokens = tokens->next;
	}
}
