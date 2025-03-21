#include "../includes/minishell.h"

void	ft_error(char *s, int code, t_base *base)
{
	base->exit_code = code;
	ft_putstr_fd(s, 2);
	/* if (getpid() == 0)
	{
		ft_putstr_fd("ERREUR D'UN ENFANT", 2);
		exit (base->exit_code);
	} */
}

int	check_only_redirect(t_token *tokens, t_base *base)
{
	t_token *current;

	current = tokens;
	if (ft_strcmp(current->data, "||") && !current->next)
		return (ft_error("minishel: syntax error near unexpected token `||'", 2, base), 1);
	else if (current->data[0] == '|' && !current->next)
		return (ft_error("minishel: syntax error near unexpected token `|'", 2, base), 1);
	while (current)
	{
		if (current->data[0] == '<' && !current->next)
			return (ft_error("minishell: syntax error near unexpected token `newline'", 2, base), 1);
		else if (current->data[0] == '>' && !current->next)
			return (ft_error("minishell: syntax error near unexpected token `newline'", 2, base), 1);
		current = current->next;
	}
	return (0);
}

void	print_double(int id, t_base *base)
{
	if (id == 3)
		ft_error("minishell: syntax error near unexpected token `<'", 2, base);
	else if (id == 4)
		ft_error("minishell: syntax error near unexpected token `>'", 2, base);
	else if (id == 5)
		ft_error("minishell: syntax error near unexpected token `<<'", 2, base);
	else if (id == 6)
		ft_error("minishell: syntax error near unexpected token `>>'", 2, base);
	else if (id == 7)
		ft_error("minishell: syntax error near unexpected token `|'", 2, base);
}

int	check_double_pippe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->next && current->id >= 3 && current->id <= 7)
		{
			if (current->id == current->next->id)
				return (print_double(current->id, current->base), 1);
		}
		current = current->next;
	}
	return (0);
}
