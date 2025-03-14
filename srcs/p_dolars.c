#include "../includes/minishell.h"

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