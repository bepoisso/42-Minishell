#include "../includes/parser.h"

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
		i++;
	}
	if (single % 2 != 0 || multi % 2 != 0)
		return (1);
	return (0);
}

int	skip_quote(char *s, int	i)
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

