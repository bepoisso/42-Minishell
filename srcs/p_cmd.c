#include "../includes/minishell.h"

t_cmd	*create_cmd(char **value)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	ft_memset(new, 0, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_cmd(t_cmd **cmds, char **value)
{
	t_cmd	*new;
	t_cmd	*temp;

	if (!value)
		return ;
	new = create_cmd(value);
	if (!new)
		return ;
	if (!*cmds)
		*cmds = new;
	else
	{
		temp = *cmds;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

int	count_args(t_token *token)
{
	int		count;
	t_token	*current;

	current = token;
	count = 0;
	while (current && current->id != 9)
		current = current->next;
	if (current && current->id == 9)
		count++;
	if (current && current->next)
		current = current->next;
	while (current && current->id != 9)
	{
		if (current->id == 10)
			count++;
		current = current->next;
	}
	return (count);
}

t_cmd	*parsing_cmd(t_base *base)
{
	t_cmd	*cmds;
	t_token	*tokens;
	char	**value;
	int		i;

	tokens = base->token;
	cmds = NULL;
	while (tokens)
	{
		i = -1;
		//value = malloc(sizeof(char *) * (count_args(tokens) + 1));
		value = ft_calloc((count_args(tokens) + 1), sizeof(char *));
		if (!value)
			return (NULL);
		while (tokens && (tokens->id == 9 || tokens->id == 10 || tokens->id == 11))
		{
			value[++i] = ft_strdup(tokens->data);
			tokens = tokens->next;
		}
		value[++i] = NULL;
		if (value[0])
			add_cmd(&cmds, value);
		else
			free_doubletab(&value);
		if (tokens && tokens->id != 9 && tokens->id != 10)
			tokens = tokens->next;
	}
	return (cmds);
}

void	identify_builtin(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (ft_strcmp("echo", current->cmd[0])
			|| ft_strcmp("cd", current->cmd[0])
			|| ft_strcmp("pwd", current->cmd[0])
			|| ft_strcmp("export", current->cmd[0])
			|| ft_strcmp("unset", current->cmd[0])
			|| ft_strcmp("env", current->cmd[0]))
			current->builtin = true;
		else
			current->builtin = false;
		current = current->next;
	}
}
