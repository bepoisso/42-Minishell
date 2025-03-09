#include "../includes/minishell.h"

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Prints the commands stored in the base structure.
 *
 * This function iterates through the linked list of commands in the base
 * structure and prints each command's name, input, and output values.
 *
 * @param base Pointer to the base structure containing the commands.
 */
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

void	isattyornot(char *cmd)
{
	if(!cmd)
		return;
	if (isatty(STDIN_FILENO)) {
		printf("L'entrée standard est un terminal pour %s\n", cmd);
	} else {
		printf("L'entrée standard n'est pas un terminal pour %s\n", cmd);
	}

	if (isatty(STDOUT_FILENO)) {
		printf("La sortie standard est un terminal pour %s\n", cmd);
	} else {
		printf("La sortie standard n'est pas un terminal pour %s\n", cmd);
	}
}


/* Affiche la liste des commandes */
void display_cmd_list(t_cmd *cmd_list)
{
	t_cmd *cur = cmd_list;
	printf("=== Liste des commandes ===\n");
	while (cur)
	{
		printf("Commande: ");
		if (cur->cmd)
		{
			for (int i = 0; cur->cmd[i] != NULL; i++)
				printf("'%s' ", cur->cmd[i]);
		}
		else
			printf("(null)");
		printf("\n");
		printf("  Path_cmd: %s\n", cur->path_cmd ? cur->path_cmd : "(null)");
		printf("  Builtin: %s\n", cur->builtin ? "true" : "false");
		cur = cur->next;
	}
}

/* Affiche la liste des tokens */
void display_token_list(t_token *token_list)
{
	t_token *cur = token_list;
	printf("=== Liste des tokens ===\n");
	while (cur)
	{
		printf("Token: data='%s', id=%d, literal=%s\n",
			   cur->data ? cur->data : "(null)",
			   cur->id,
			   cur->literal ? "true" : "false");
		cur = cur->next;
	}
}

/* Affiche le contenu complet de la structure base */
void display_base(t_base *base)
{
	if (!base)
	{
		printf("La structure base est NULL\n");
		return;
	}
	printf("===== Contenu de la structure base =====\n");
	printf("Exit Code: %d\n", base->exit_code);
	printf("Count Forks: %d\n", base->count_forks);
	
	// Afficher la liste des chemins
	if (base->path_list)
	{
		printf("Liste des chemins (path_list):\n");
		for (int i = 0; base->path_list[i] != NULL; i++)
			printf("  [%d] %s\n", i, base->path_list[i]);
	}
	else
		printf("Path_list est NULL\n");

		// Afficher la liste des commandes
	if (base->cmds)
		display_cmd_list(base->cmds);
	else
		printf("Aucune commande dans base->cmds.\n");

	// Afficher la liste des tokens
	if (base->token)
		display_token_list(base->token);
	else
		printf("Aucun token dans base->token.\n");

	printf("========================================\n");
}
