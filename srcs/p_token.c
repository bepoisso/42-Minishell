#include "../includes/minishell.h"

t_token	*create_token(char *value, bool literal, t_base *base)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	ft_memset(new, 0, (sizeof(t_token)));
	if (!new)
		return (NULL);
	new->data = ft_strdup(value);
	new->literal = literal;
	new->next = NULL;
	new->prev = NULL;
	new->base = base;
	return (new);
}

void	add_token(t_token **tokens, char *value, bool literal, t_base *base)
{
	t_token	*new;
	t_token	*temp;

	if (!value)
		return ;
	new = create_token(value, literal, base);
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
	free_null((void **)&value);
}

void	rm_node_token(t_token *token)
{
	t_token	*next;
	t_token	*prev;

	if (!token)
		return;
	free_null((void **)&token->data);
	next = token->next;
	prev = token->prev;
	if (prev)
		prev->next = token->next;
	if (next)
		next->prev = token->prev;
	free_null((void **)&token);
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
		add_token(&tokens, ft_strndup(s + start, i - start), literal, base);
	}
	return (tokens);
}

void	identify_token(t_token *tokens)
{
	t_token	*current;
	int		cmd;
	int		redir;

	cmd = 0;
	redir = 0;
	current = tokens;
	while (current)
	{
		current->id = get_op_token(current->data, current->id);
		if ((current->id >= 3 && current->id <= 6))
			redir = 1;
		if (current->id >= 1 && current->id <= 7)
			cmd = 0;
		if (current->id == -1)
		{
			if (redir == 1)
			{
				current->id = get_redir_io(current);
				redir = 0;
			}
			else if (cmd == 0)
			{
				current->id = 9;
				cmd = 1;
			}
			else if (current->id != 0)
				current->id = 10;
		}
		current = current->next;
	}
}
