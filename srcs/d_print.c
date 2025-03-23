

#include "../includes/minishell.h"

void	ft_put_arraystr(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		ft_printf("--------------------------------------------------------------------\n");
		while (array[i])
		{
			ft_printf("\t[%s]\n", array[i]);
			i++;
		}
		ft_printf("--------------------------------------------------------------------\n");
	}
}

void	print_cmds(t_base *base)
{
	t_cmd	*actual;

	actual = base->cmds;
	while(actual)
	{
		printf(GREEN"commande : %s input : %d output : %d\n"RESET, actual->cmd[0], actual->input, actual->output);
		actual = actual->next;
	}
}

/* Affiche la liste des commandes */
void    display_cmd_list(t_cmd *cmd_list)
{
	t_cmd *cur = cmd_list;
   ft_printf("=== Liste des commandes ===\n");
	while (cur)
	{
	   ft_printf("Commande: ");
		if (cur->cmd)
		{
			for (int i = 0; cur->cmd[i] != NULL; i++)
			   ft_printf("'%s' ", cur->cmd[i]);
		}
		else
		   ft_printf("(null)");
	   ft_printf("\n");
	   ft_printf("  Path_cmd: %s\n", cur->path_cmd ? cur->path_cmd : "(null)");
	   ft_printf("  Builtin: %s\n", cur->builtin ? "true" : "false");
		cur = cur->next;
	}
}

/* Affiche la liste des tokens */
void    display_token_list(t_token *token_list)
{
	t_token *cur = token_list;
   ft_printf("=== Liste des tokens ===\n");
	while (cur)
	{
	   ft_printf("Token: data='%s', id=%d, literal=%s\n",
			   cur->data ? cur->data : "(null)",
			   cur->id,
			   cur->literal ? "true" : "false");
		cur = cur->next;
	}
}

/* Affiche le contenu complet de la structure base */
void    display_base(t_base *base)
{
	if (!base)
	{
	   ft_printf("La structure base est NULL\n");
		return;
	}
   ft_printf("===== Contenu de la structure base =====\n");
   ft_printf("Exit Code: %d\n", base->exit_code);
   ft_printf("Count Forks: %d\n", base->count_forks);
	
	// Afficher la liste des chemins
	if (base->path_list)
	{
	   ft_printf("Liste des chemins (path_list):\n");
		for (int i = 0; base->path_list[i] != NULL; i++)
		   ft_printf("  [%d] %s\n", i, base->path_list[i]);
	}
	else
	   ft_printf("Path_list est NULL\n");

		// Afficher la liste des commandes
	if (base->cmds)
		display_cmd_list(base->cmds);
	else
	   ft_printf("Aucune commande dans base->cmds.\n");

	// Afficher la liste des tokens
	if (base->token)
		display_token_list(base->token);
	else
	   ft_printf("Aucun token dans base->token.\n");

   ft_printf("========================================\n");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: id : [%d] [%d] [%s]\n", tokens->id, tokens->literal, tokens->data);
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
		printf("\nCMD : %s [%d]\n", current->cmd[i], current->builtin);
		i++;
		while (current->cmd[i])
		{
			printf("arg : %s\n", current->cmd[i]);
			i++;
		}
		current = current->next;
	}
	current = base->cmds;
}

void	print_dollar(t_base *base)
{
	t_dollar *current;

	current = base->dollars;
	printf("\n__________DOLLARS__________\n");
	while (current)
	{
		printf("Dollar = [%s] [%s] [%d]\n", current->name, current->data, current->literal);
		current = current->next;
	}
}