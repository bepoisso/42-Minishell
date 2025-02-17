#include "../includes/parser.h"

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

t_token	*tokenizer(char *s)
{
	int		i;
	int		start;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		start = i;
		if (s[i] == '"' || s[i] == '\'')
		{
			i = skip_quote(s, i);
			start++;
		}
		else
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '"' && s[i] != '\'')
				i++;
		add_token(&tokens, ft_strndup(s + start, i - start));
	}
	return (tokens);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%s]\n", tokens->data);
		tokens = tokens->next;
	}
}