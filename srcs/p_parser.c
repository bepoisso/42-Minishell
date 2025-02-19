#include "../includes/minishell.h"

void	init_base(t_base *base)
{
	base->exit_code = 0;
}

/* void	split_args(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ()
		i++;
	}
} */

t_token	*parser(char *str, char **env)
{
	int		i;
	char	*start;
	char	*end;
	bool	check;
	t_base	base;
	t_token	*tokens;

	i = 0;
	check = false;
	init_base(&base);
	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, &base), NULL);
	tokens = tokenizer(str);
	print_tokens(tokens);
	return (tokens);
}
