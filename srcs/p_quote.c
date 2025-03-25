#include "../includes/minishell.h"

int	check_quote(char c, char *str, int *i)
{
	int	val;

	val = 0;
	if (str[*i] == c)
	{
		val++;
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		if (str[*i] == c)
			val++;
	}
	return (val);
}

int	open_quote(char *str)
{
	int	single;
	int	multi;
	int	i;

	i = 0;
	single = 0;
	multi = 0;
	while (str[i])
	{
		single += check_quote((char)39, str, &i);
		multi += check_quote((char)34, str, &i);
		if (!str[i])
			break ;
		i++;
	}
	if (single % 2 != 0 || multi % 2 != 0)
		return (1);
	return (0);
}

int	skip_quote(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static void	remove_quotes_from_data(char *data, char **result)
{
	int		i;
	int		j;
	int		in;

	i = -1;
	j = 0;
	in = 0;
	*result = malloc(sizeof(char) * (ft_strlen(data) + 1));
	ft_memset(*result, 0, sizeof(char) * (ft_strlen(data) + 1));
	while (data[++i])
	{
		if (data[i] == '"' && in == 0)
			in = 1;
		else if (data[i] == '\'' && in == 0)
			in = 2;
		else if (data[i] == '"' && in == 1)
			in = 0;
		else if (data[i] == '\'' && in == 2)
			in = 0;
		else
			(*result)[j++] = data[i];
	}
}

void	rm_quote(t_token *tokens)
{
	t_token	*current;
	char	*temp;

	current = tokens;
	while (current)
	{
		if (current && (ft_strchr(current->data, '\'')
				|| ft_strchr(current->data, '"')))
		{
			remove_quotes_from_data(current->data, &temp);
			free_null((void **)&current->data);
			current->data = ft_strdup(temp);
			free_null((void **)&temp);
		}
		current = current->next;
	}
}
