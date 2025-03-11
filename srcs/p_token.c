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

void	rm_node_token(t_token *token)
{
	t_token	*next;
	t_token	*prev;

	if (!token)
		return;
	next = token->next;
	prev = token->prev;
	if (prev)
		prev->next = token->next;
	if (next)
		next->prev = token->prev;
	free(token);
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

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token	*tokenizer(char *s, t_base *base)
{
	int		i;
	int		start;
	t_token	*tokens;
	bool	literal;
	(void)base;
	tokens = NULL;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (tokens);
	while (s[i])
	{
		literal = false;
		if (ft_isspace(s[i]))
		{
			start = i;
			while (ft_isspace(s[i]))
				i++;
		}
		else if (ft_isop(s[i]))
		{
			start = i;
			while (ft_isop(s[i]))
				i++;
		}
		else if (s[i] == '"' || s[i] == '\'')
		{
			if (s[i] == '\'')
				literal = true;
			start = i;
			i = skip_quote(s, i);
		}
		else
		{
			start = i;
			while(ft_isprint(s[i]) && !ft_isop(s[i]) && !ft_isspace(s[i]) && s[i] != '\'' && s[i] != '"')
				i++;
		}
		add_token(&tokens, ft_strndup(s + start, i - start), literal);
	}
	return (tokens);
}

//            test arg         args t"es"t T'ES'T < << >> >     | || "T      ES        T" 't    est     '
