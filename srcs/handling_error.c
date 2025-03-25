#include "../includes/minishell.h"

int	handling_error(t_base *base)
{
	if (base->input[0] == '\0' || base->input[0] == '\n')
	{
		free_null((void **)&base->input);
		return (1);
	}
	if (parser(base->input, base))
	{
		add_history(base->input);
		free_null((void **)&base->input);
		return (1);
	}
	if (!base->token)
		return (1);
	return (0);
}
