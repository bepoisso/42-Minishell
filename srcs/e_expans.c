#include "../includes/minishell.h"

static int	ft_is_only(char *s, int index)
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	while (s[i] && i <= index)
	{
		if (s[i] == '?' && check == false)
		{
			check = true;
			if (i == index)
				return (1);
		}
		else if (s[i] == '?' && check == true && i == index)
			break ;
		i++;
	}
	return (0);
}

int	give_me_dols(char *s, int nbr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (count == nbr)
				return (i);
			else
				count ++;
		}
		i++;
	}
	return (-1);
}

static void	change_dollars(t_token *tok, t_dollar *current,
							char *buff, int *count)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (tok->data[i])
	{
		if (tok->data[i] == '$' && (*count)++ != -1)
		{
			k = 0;
			while (current->data[k])
				buff[j++] = current->data[k++];
			current = current->next;
			i++;
			while (ft_isalnum(tok->data[i]) || ft_is_only(tok->data, i))
				i++;
		}
		else
			buff[j++] = tok->data[i++];
	}
	buff[j] = '\0';
	free(tok->data);
	tok->data = ft_strndup(buff, ft_strlen(buff));
}

void	expanse(t_token *tokens, t_dollar *dollars)
{
	t_token		*tok;
	t_dollar	*dol;
	char		buff[BUFF];
	int			count;

	tok = tokens;
	dol = dollars;
	while (tok)
	{
		if (ft_strchr(tok->data, '$'))
		{
			count = 0;
			change_dollars(tok, dol, buff, &count);
			while (dol && count-- != 0)
				dol = dol->next;
		}
		tok = tok->next;
	}
}
