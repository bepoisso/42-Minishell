#include "../includes/minishell.h"

static void	lexer_args(char *s, int *i, int *start)
{
	*start = *i;
	while (ft_isprint(s[*i]) && !ft_isop(s[*i]) && !ft_isspace(s[*i])
		&& s[*i] != '\'' && s[*i] != '"')
		(*i)++;
}

static void	lexer_quote(char *s, int *i, int *start, bool *literal)
{
	if (s[*i] == '\'')
		*literal = true;
	*start = *i;
	*i = skip_quote(s, *i);
}

static void	lexer_op(char *s, int *i, int *start)
{
	*start = *i;
	while (ft_isop(s[*i]))
		(*i)++;
}

static void	lexer_space(char *s, int *i, int *start)
{
	*start = *i;
	while (ft_isspace(s[*i]))
		(*i)++;
}

t_token	*lexer(char *s, t_base *base)
{
	int		i;
	int		start;
	t_token	*tokens;
	bool	literal;

	tokens = NULL;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (tokens);
	while (s[i])
	{
		literal = false;
		if (ft_isspace(s[i]))
			lexer_space(s, &i, &start);
		else if (ft_isop(s[i]))
			lexer_op(s, &i, &start);
		else if (s[i] == '"' || s[i] == '\'')
			lexer_quote(s, &i, &start, &literal);
		else
			lexer_args(s, &i, &start);
		add_token(&tokens, ft_strndup(s + start, i - start), literal, base);
	}
	return (tokens);
}
