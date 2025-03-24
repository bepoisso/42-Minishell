#include "../includes/minishell.h"

t_token	*create_token(char *value, bool literal, t_base *base)
{
	t_token	*new;

	if (!value)
		return (NULL);
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
		return ;
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
		return ;
	free_null((void **)&token->data);
	next = token->next;
	prev = token->prev;
	if (prev)
		prev->next = token->next;
	if (next)
		next->prev = token->prev;
	free_null((void **)&token);
}

static void	set_redir_or_cmd(t_token *current, int *redir, int *cmd)
{
	if (*redir == 1)
	{
		current->id = get_redir_io(current);
		*redir = 0;
	}
	else if (*cmd == 0)
	{
		current->id = 9;
		*cmd = 1;
	}
	else if (current->id != 0)
		current->id = 10;
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
		if (current->id == 7)
			cmd = 0;
		if (current->id == -1)
			set_redir_or_cmd(current, &redir, &cmd);
		current = current->next;
	}
}
