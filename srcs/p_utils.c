#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

int	start_pipe(char *s, t_base *base)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
			return (ft_error(RED"minishell: syntax error near \
unexpected token `||'\n"RESET, 2, base), 1);
		else if (s[i] == '|')
			return (ft_error(RED"minishell: syntax error near \
unexpected token `|'\n"RESET, 2, base), 1);
		else if (s[i] == '&' && s[i + 1] == '&')
			return (ft_error(RED"minishell: syntax error near \
unexpected token `&&'\n"RESET, 2, base), 1);
		else if (s[i] == '&')
			return (ft_error(RED"minishell: syntax error near \
unexpected token `&'\n"RESET, 2, base), 1);
		else if (s[i] == ':' || s[i] == '!')
			return (ft_error(RED"minishell: syntax error near \
unexpected token `newline'\n"RESET, 2, base), 1);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	no_quote(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->id == 11)
			return (1);
		current = current->next;
	}
	return (0);
}
