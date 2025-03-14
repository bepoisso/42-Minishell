#include "../includes/minishell.h"

int	parser(char *str, t_base *base)
{
	t_token	*tokens;

	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, base), 1);
	tokens = tokenizer(str, base);
	base->token = tokens;
	return (0);
}

char	*search_env_var(char *search)
{
	extern char	**environ; //Remplacer par notre environ
	int			i;
	int			j;

	i = 0;
	j = 0;
	while(environ[j])
	{
		if (ft_strncmp(search, environ[i], ft_strlen(search)) == 0)
		{
			j = ft_strlen(search) + 1;
			if (environ[i][j] == '=')				
				return (free(search), ft_strdup(environ[i] + j));
		}
		i++;
	}
	return (free(search), NULL);
}

void	search_dolars(t_token *tokens)
{
	t_token		*current;
	int			i;
	int			j;
	char		*temp;

	current = tokens;
	while (current)
	{
		i = 0;
		if (current->id == 11 && current->literal == false)
		{
			while (current->data[i])
			{
				if (current->data[i] == '$')
				{
					j = i;
					while (current->data[j] && (current->data[j] != ' ' || current->data[j] != '\'' || current->data[j] != '"'))
						j++;
					temp = ft_strndup(current->data + (i + 1), j - i);
					temp = search_env_var(temp);
					if (!temp)
					{
						i++;
						continue;
					}
					// remlacer $VAR par temp
					break;
				}
				i++;
			}
		}
		current = current->next;
	}
}

void	rm_quote(t_token *tokens)
{
	t_token	*current;
	char	*temp;
	int		i;
	int		j;

	current = tokens;
	i = -1;
	j = 0;
	while (current)
	{
		if (current && (ft_strchr(current->data, '\'') || ft_strchr(current->data, '"')))
		{
			temp = malloc(sizeof(char) * (ft_strlen(current->data) + 1));
			ft_memset(temp, 0, sizeof(char) * (ft_strlen(current->data) + 1));
			while (current->data[++i])
			{
				if (!(current->data[i] == '\'' || current->data[i] == '"'))
				{
					temp[j] = current->data[i];
					j++;
				}
			}
			temp[j] = '\0';
			free(current->data);
			current->data = ft_strdup(temp);
			free(temp);
		}
		current = current->next;
	}
}

t_token	*token_parser(t_token *tokens)
{
	t_token	*current;
	t_token	*save;
	char	*temp;

	current = tokens;
	temp = NULL;
	while (current)
	{
		if (!ft_isop(current->data[0]) && current->id != 0)
		{
			if (current->next && (current->next->id == 11 || (current->id == 11 && !ft_isop(current->next->data[0]) && current->next->id != 0)) )
			{
				temp = ft_strdup(current->data);
				current->id = 11;
				current->literal = current->next->literal;
				free(current->data);
				current->data = ft_strjoin(temp, current->next->data);
				rm_node_token(current->next);
				continue;
			}
		}
		current = current->next;
	}
	current = tokens;
	while (1)
	{
		 if (!current)
			break ;
		save = current->next;
		if (current->id == 0)
		{
			if (current == tokens)
			tokens = tokens->next;
			rm_node_token(current);
		}
		if (save == NULL)
			break;
		current = save;
	}
	identify_token(tokens);
	printf("----------1----------\n");
	print_tokens(tokens);
	search_dolars(tokens);
	rm_quote(tokens);
	printf("----------2----------\n");
	print_tokens(tokens);
	return (tokens);
}

