#include "../includes/minishell.h"

void	ft_put_arraystr(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		ft_printf("------------------------------------------------------\n");
		while (array[i])
		{
			ft_printf("\t[%s]\n", array[i]);
			i++;
		}
		ft_printf("------------------------------------------------------\n");
	}
}

void	print_cmds(t_base *base)
{
	t_cmd	*actual;

	actual = base->cmds;
	while (actual)
	{
		ft_printf(GREEN"commande : %s input : %d output : %d\n"RESET,
			actual->cmd[0], actual->input, actual->output);
		actual = actual->next;
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Token: id : [%d] [%d] [%s]\n", tokens->id,
			tokens->literal, tokens->data);
		tokens = tokens->next;
	}
}

void	print_cmd(t_base *base)
{
	t_cmd	*current;
	int		i;

	current = base->cmds;
	while (current)
	{
		i = 0;
		ft_printf("\nCMD : %s [%d]\n", current->cmd[i], current->builtin);
		i++;
		while (current->cmd[i])
		{
			ft_printf("arg : %s\n", current->cmd[i]);
			i++;
		}
		current = current->next;
	}
	current = base->cmds;
}

void	print_dollar(t_base *base)
{
	t_dollar	*current;

	current = base->dollars;
	ft_printf("\n__________DOLLARS__________\n");
	while (current)
	{
		ft_printf("Dollar = [%s] [%s] [%d]\n", current->name,
			current->data, current->literal);
		current = current->next;
	}
}
