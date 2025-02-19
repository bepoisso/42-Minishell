#include "../includes/minishell.h"

/**Idem a what next mais dans l'autre sens
 * 
 */
static int	what_before(t_token *act_tok, t_base *base, int i)
{
	t_token	*tokencpy;

	tokencpy = act_tok;
	while (tokencpy->prev)
	{
		if (tokencpy->id >= 3 && tokencpy->id <= 7)
		{
			if (tokencpy->id == 3 || tokencpy->id == 5)
				return (printf("redirect infile"), 3);//a faire
			if (tokencpy->id == 4 || tokencpy->id == 6)
				return (printf("redirect outfile"), 2);//a faire
			if (tokencpy->id == 7)
				return (dup2(base->pipes[act_tok->index_pipe][1], STDIN_FILENO)
					, close(base->pipes[i - 1][1]), 1);
			tokencpy = tokencpy->prev;
		}
	}
	return (0);
}

/**
 * check si il y aune redirection avant la commande et gere les
 *  redirections et pipes si il y en as
 */
static int	what_after(t_token *act_tok, t_base *base, int i)
{
	t_token	*tokencpy;

	tokencpy = act_tok;
	while (act_tok->next)
	{
		if (tokencpy->id >= 3 && tokencpy->id <= 7)
		{
			if (tokencpy->id == 3 || tokencpy->id == 5)
				return (printf("redirect infile"), 3);//a faire
			if (tokencpy->id == 4 || tokencpy->id == 6)
				return (printf("redirect outfile"), 2);//a faire
			if (tokencpy->id == 7)
				return (dup2(base->pipes[act_tok->index_pipe][0], STDOUT_FILENO)
					, base->pipes_index++, 1);
			tokencpy = tokencpy->prev;
		}
	}
	return (0);
}

/**fonction qui va gere la fermeture de tous les fd non utilise dans les forks
 * le premier parametre est l'index dans le tableau de pipes du fd a conserver
 * si il est a -1 on efface tout
 * les second et troisiemes parametres indiquent si il faut supprimer le in, le
 * out, les deux ou aucun.
 * le troisieme parametre est la base, pour recuperer le tableau de pipes
 */
void	close_fds(int keep_open, int in, int out, t_base *base)
{
	int	i;

	i = 0;
	while (i < base->count_pipe)
	{
		if (i == keep_open)
		{
			if (in)
				close(base->pipes[i][0]);
			if (out)
				close(base->pipes[i][1]);
		}
		else
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
 * Fonction close_fd a ecrire
 * gestion des erreurs a faire
 */
int	prepare_exec(t_cmd *actual_cmd, t_token *act_tok, t_base *base)
{
	pid_t	pid;
	int		redir_in;
	int		redir_out;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		redir_in = what_before(act_tok, base, base->pipes_index);
		if (redir_in == 0)
			close_fds(1, 0, -1, base);
		redir_out = what_after(act_tok, base, base->pipes_index);
		if (redir_out == 0)
			close_fds(0, 1, -1, base);
	}
	return (0);
}
