#include "../includes/minishell.h"

/**
 * @brief Handles the operations to be performed before executing a command.
 *
 * This function iterates through the tokens and performs necessary actions
 * based on the token's ID. It handles file redirections and pipe duplications.
 *
 * @param act_tok Pointer to the current token.
 * @param base Pointer to the base structure containing pipe information.
 * @return int Returns 1 if there is an error in file redirection, otherwise 0.
 */

static int	what_before(t_token *act_tok, t_base *base)
{
	t_token	*actual;

	actual = act_tok;
	while (actual)
	{
		if (actual->id >= 3 && actual->id <= 6)
		{
			cls_pipes(-1, 1, 1, base);
			if (file_redir(actual, base))
				return (1);
			return (0);
		}
		else if (actual->id == 7)
		{
			return (dup2(base->pipes[actual->index_pipe][0], STDIN_FILENO)
			, cls_pipes(-1, 1, 0, base), 0);
		}
		actual = actual->prev;
	}
	cls_pipes(-1, 1, 0, base);
	return (0);
}

/**
 * what_after - Handles the execution flow based on the token ID.
 * @act_tok: Pointer to the current token.
 * @base: Pointer to the base structure containing necessary data.
 *
 * This function iterates through the tokens starting from @act_tok and performs
 * actions based on the token ID. If the token ID is between 3 and 6, it closes
 * pipes, performs file redirection, and returns 1 on success or 0 otherwise.
 * If the token ID is 7, it duplicates the pipe file descriptor to STDOUT,
 * closes the read end of the pipe, closes other pipes, and returns 0.
 * If no specific action is required, it closes pipes and returns 0.
 *
 * Return: 1 if file redirection is successful, 0 otherwise.
 */
static int	what_after(t_token *act_tok, t_base *base)
{
	t_token	*actual;

	actual = act_tok;
	while (actual)
	{
		if (actual->id >= 3 && actual->id <= 6)
		{
			cls_pipes(-1, 1, 1, base);
			if (file_redir(actual, base))
				return (1);
			return (0);
		}
		else if (actual->id == 7)
		{
			return (dup2(base->pipes[actual->index_pipe][1], STDOUT_FILENO)
			, cls_pipes(-1, 0, 1, base), 0);
		}
		actual = actual->next;
	}
	cls_pipes(-1, 0, 1, base);
	return (0);
}

/**fonction qui va gere la fermeture de tous les fd non utilise dans les forks
 * le premier parametre est l'index dans le tableau de pipes du fd a conserver
 * si il est a -1 on efface tout
 * les second et troisiemes parametres indiquent si il faut supprimer le in, le
 * out, les deux ou aucun. 1 pour supprimer, 0 conserver
 * le troisieme parametre est la base, pour recuperer le tableau de pipes
 */
void	cls_pipes(int keep_open, int in, int out, t_base *base)
{
	int	i;

	i = 0;
	while (i < base->count_pipe)
	{
		if (i != keep_open)
		{
			if (in)
				close(base->pipes[i][0]);
			if (out)
				close(base->pipes[i][1]);
		}
		i++;
	}
}

/**
 * actual_cmd->path_cmd A FREE A LA FIN !!!!!!
 * gestion des erreurs a faire
 * CHANGER POUR FONCTION QUI PRINT DANS FD2
 * fonction a raccourcir
 */
void	prepare_exec(t_cmd *actual_cmd, t_token *act_tok, t_base *base)
{
	pid_t		pid;
	extern char	**environ;

	pid = fork();
	if (pid == -1)
	{
		perror("Error create fork\n");
		clean_exit(base, -1);
	}
	if (pid == 0)
	{
		what_before(act_tok->prev, base);
		what_after(act_tok->next, base);
		actual_cmd->path_cmd = check_cmd(base->path_list, act_tok->data, base);
		if (!actual_cmd->path_cmd)
			clean_exit(base, 127);
		base->exit_code = execve(actual_cmd->path_cmd, actual_cmd->cmd, environ);
		/* if (actual_cmd->builtin)
			//handle_builtin();//fonction gestion builtin
		else
			execve(actual_cmd->path_cmd, actual_cmd->cmd, environ); */
	/* 	if (errno)
		clean_exit(base, errno); */
		write(2, "POUET\n", 6);
		cls_pipes(1, 1, -1, base);
		clean_exit(base, base->exit_code);
	}
}
