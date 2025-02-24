#include "../includes/minishell.h"

t_cmd	*create_cmd(char **value)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
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

void	print_cmd(t_base *base)
{
	t_cmd	*current;
	int		i;

	current = base->cmds;
	while (current)
	{
		i = 0;
		printf("\nCMD : %s\n", current->cmd[i]);
		i++;
		while (current->cmd[i])
		{
			printf("arg : %s\n", current->cmd[i]);
			i++;
		}
		current = current->next;
	}
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
		value = malloc(sizeof(char *) * (count_args(tokens) + 1));
		if (!value)
			return (NULL);
		while (tokens && (tokens->id == 9 || tokens->id == 10))
		{
			value[++i] = ft_strdup(tokens->data);
			tokens = tokens->next;
		}
		value[++i] = NULL;
		if (value[0])
			add_cmd(&cmds, value);
		if (tokens && tokens->id != 9 && tokens->id != 10)
			tokens = tokens->next;
	}
	return (cmds);
}
