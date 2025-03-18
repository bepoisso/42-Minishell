#include "../includes/minishell.h"

char	*search_env_var(char *search, char **env)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while(env[i])
	{
		if (ft_strncmp(search, env[i], ft_strlen(search)) == 0)
		{
			j = ft_strlen(search);
			if (env[i][j] == '=')
				return (ft_strdup(env[i] + (j + 1)));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	dollar_is_literal(t_dollar *dollars)
{
	int		i;
	char	*temp;
	t_dollar *current;

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


t_dollar	*create_dollar(char *value ,char *name , bool literal)
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

void	add_dollar(t_dollar **dollars,char *name, char *value, bool literal)
{
	t_dollar	*new;
	t_dollar	*temp;

	if (!value)
		return ;
	new = create_dollar(value, name, literal);
	if (!new)
		return;
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

	i = 0;
	while (token && token->data[i])
	{
		if (token->data[i] == '$')
		{
			j = i;
			i++;
			while (token->data[i] && ft_isalnum(token->data[i]))
				i++;
			name = ft_strndup(token->data + j + 1, (i - j) - 1);
			data = search_env_var(name, base->env);
			add_dollar(&dollars, name, data, token->literal);
		}
		if (!token->data[i])
			break;
		i++;
	}
}

void	handling_dollar(t_token *tokens, t_base *base)
{
	t_dollar	*dollars;
	t_token		*current;

	free(base->dollars);
	dollars = malloc(sizeof(t_dollar));
	ft_memset(dollars, 0, sizeof(t_dollar));
	current = tokens;

	while (current)
	{
		get_name_value_dollar(current, dollars, base);
		current = current->next;
	}
	base->dollars = dollars;
	base->dollars = dollars->next;
	free(dollars->prev);
}