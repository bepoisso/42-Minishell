#include "../includes/minishell.h"

void	parser(char *str, t_base *base)
{
	t_token	*tokens;

	if (open_quote(str) != 0)
		return (ft_error("ERROR\nopen quote", 1, base));
	tokens = tokenizer(str, base);
	base->token = tokens;
}
