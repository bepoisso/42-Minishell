#include "../includes/minishell.h"

char	*search_env_var(char *search, char **env)
{
	int			i;
	int			j;
	char		*temp; // a suppre

	i = 0;
	j = 0;
	while(env[i])
	{
		if (ft_strncmp(search, env[i], ft_strlen(search)) == 0)
		{
			j = ft_strlen(search);
			if (env[i][j] == '=')
			{
				temp = ft_strdup(env[i] + (j + 1));
				return (free_null((void **)&search), temp);
			}
		}
		i++;
	}
	return (free_null((void **)&search), NULL);
}

char	*replace_dolars_var(t_token *token, char *var)
{
	int	i;
	int	j;
	char	*temp_before;
	char	*temp_after;

	temp_before = NULL;
	temp_after = NULL;
	i = 0;
	j = 0;
	while (token->data[i] && token->data[i] != '$')
		i++;
	i++;
	temp_before = ft_strndup(token->data, i);
	while (token->data[i] != ' ' || token->data[i] != '$')
		i++;
	i = j;
	while (token->data[i])
		i++;
	temp_after = ft_strndup(token->data + j, i - j);
	// Faire les join de tout ca et c'est bon
	return (NULL); // renvoyer le resultat du join
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
		if (current && current->literal == false)
		{
			while (current->data[i])
			{
				if (current->data[i] == '$')
				{
					j = i;
					while (current->data[j] && (current->data[j] != ' ' || current->data[j] != '\'' || current->data[j] != '"'))
						j++;
					temp = ft_strndup(current->data + (i + 1), j - i);
					temp = search_env_var(temp, tokens->base->env);
					if (!temp)
					{
						i++;
						continue;
					}
					replace_dolars_var(current, temp);
					break;
				}
				i++;
			}
		}
		current = current->next;
	}
}
