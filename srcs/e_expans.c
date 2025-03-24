#include "../includes/minishell.h"

static int ft_is_only(char *s, int index)
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

static void	change_dollars(t_token *tok, t_dollar *dol)
{
	char	*before;
	char	*temp;
	char	*after;
	int		i;

	i = 0;
	while (tok->data[i] && tok->data[i] != '$')
		i++;
	if (tok->data[i] != '$')
		return;
	if (i == 0)
		before = ft_strdup("");
	else
		before = ft_strndup(tok->data, i);
	i++;
	while (tok->data[i] && (ft_isalnum(tok->data[i]) || ft_is_only(tok->data, i)))
		i++;
	after = ft_strdup(tok->data + i);
	temp = ft_strjoin(before, dol->data);
	free(tok->data);
	tok->data = ft_strjoin(temp, after);
	free(temp);
	free(before);
	free(after);
}

void	expanse(t_token *tokens, t_dollar *dollars)
{
	t_token		*tok;
	t_dollar	*dol;

	tok	= tokens;
	dol = dollars;
	while (tok)
	{
		if (ft_strchr(tok->data, '$'))
		{
			change_dollars(tok, dol);
			dol = dol->next;
		}
		if (ft_strchr(tok->data, '$'))
			continue ;
		tok = tok->next;
	}
}
