#include "../includes/minishell.h"

void	dollar_is_literal(t_dollar *dollars)
{
	int			i;
	char		*temp;
	t_dollar	*current;

	current = dollars;
	while (current)
	{
		if (current->literal == true)
		{
			free_null((void **)&current->data);
			i = 0;
			temp = malloc(sizeof(char) * ft_strlen(current->name) + 2);
			temp[i] = '$';
			while (current->name[++i - 1])
				temp[i] = current->name[i - 1];
			temp[i] = '\0';
			current->data = ft_strdup(temp);
			free(temp);
		}
		current = current->next;
	}
}

t_dollar	*create_dollar(char *value, char *name, bool literal)
{
	t_dollar	*new;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_dollar));
	ft_memset(new, 0, (sizeof(t_dollar)));
	if (!new)
		return (NULL);
	new->data = ft_strdup(value);
	new->name = ft_strdup(name);
	new->literal = literal;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_dollar(t_dollar **dollars, char *name, char *value, bool literal)
{
	t_dollar	*new;
	t_dollar	*temp;

	if (!value)
		return ;
	new = create_dollar(value, name, literal);
	if (!new)
		return ;
	if (!*dollars)
		*dollars = new;
	else
	{
		temp = *dollars;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	free_null((void **)&name);
	free_null((void **)&value);
}

void	get_name_value_dollar(t_token *token, t_dollar *dollars, t_base *base)
{
	int		i;
	int		j;
	char	*name;
	char	*data;
	bool	check;

	i = -1;
	check = false;
	while (token && token->data[++i])
	{
		if (token->data[i] == '$')
		{
			j = i;
			while (token->data[++i] && (ft_isalnum(token->data[i])
					|| token->data[i] == '_'
					|| (check == false && token->data[i] == '?')))
				check = true;
			name = ft_strndup(token->data + j + 1, (i - j) - 1);
			data = search_env_var(name, base->env, base);
			add_dollar(&dollars, name, data, token->literal);
			i--;
		}
		if (!token->data[i])
			break ;
	}
}

void	handling_dollar(t_token *tokens, t_base *base)
{
	t_dollar	*dollars;
	t_token		*current;

	if (!tokens)
		return ;
	free(base->dollars);
	dollars = malloc(sizeof(t_dollar));
	ft_memset(dollars, 0, sizeof(t_dollar));
	current = tokens;
	print_tokens(tokens); // a suppre
	while (current)
	{
		get_name_value_dollar(current, dollars, base);
		current = current->next;
	}
	print_dollar(base);
	base->dollars = dollars;
	base->dollars = dollars->next;
	free(dollars);
}
