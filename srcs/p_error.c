#include "../includes/minishell.h"

void	ft_error(char *s, int code, t_base *base)
{
	base->exit_code = code;
	ft_putstr_fd(s, 2);
	/*	A supprimer	*/
	if (base != NULL)
		ft_printf("\nexit code = %d\n", base->exit_code);
	/*			 */
	if (getpid() == 0)
		exit (base->exit_code);
}

int	check_only_redirect(t_token *tokens, t_base *base)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->data[0] == '<' && !current->next)
			return (ft_error("bash: syntax error near unexpected token `newline'", 2, base), 1);
		else if (current->data[0] == '>' && !current->next)
			return (ft_error("bash: syntax error near unexpected token `newline'", 2, base), 1);
		current = current->next;
	}
	return (0);
}
