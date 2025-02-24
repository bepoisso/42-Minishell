#include "../includes/minishell.h"

/**Idem a what next mais dans l'autre sens
 * pipes geres reste infile outfile
 */
int	what_before(t_token *act_tok, t_base *base)
{
	t_token	*tokencpy;

	tokencpy = act_tok;
	while (tokencpy)
	{
		if (tokencpy->id >= 3 && tokencpy->id <= 7)
		{
			if (tokencpy->id == 3 || tokencpy->id == 5)
				return (printf("redirect infile"), 3);
			if (tokencpy->id == 4 || tokencpy->id == 6)
				return (printf("redirect outfile"), 2);
			if (tokencpy->id == 7)
				return (dup2(base->pipes[tokencpy->index_pipe][1], STDIN_FILENO)
				, close(base->pipes[act_tok->index_pipe][0])
					, close_fds(act_tok->index_pipe, 1, 0, base), 1);
		}
		tokencpy = tokencpy->prev;
	}
	return (0);
}

/**
 * check si il y aune redirection avant la commande et gere les
 *  redirections et pipes si il y en as
 */
int	what_after(t_token *act_tok, t_base *base)
{
	t_token	*tokencpy;

	tokencpy = act_tok;
	while (tokencpy)
	{
		if (tokencpy->id >= 3 && tokencpy->id <= 7)
		{
			if (tokencpy->id == 3 || tokencpy->id == 5)
				return (close_fds(-1, 1, 1, base), 3);
			if (tokencpy->id == 4 || tokencpy->id == 6)
				return (close_fds(-1, 1, 1, base), 2);
			if (tokencpy->id == 7)
				return (dup2(base->pipes[act_tok->index_pipe][0], STDOUT_FILENO)
				, close(base->pipes[act_tok->index_pipe][1])
					, close_fds(act_tok->index_pipe, 0, 1, base), 1);
		}
		tokencpy = tokencpy->next;
	}
	close_fds(-1, 1, 1, base);
	return (0);
}

/**fonction qui va gere la fermeture de tous les fd non utilise dans les forks
 * le premier parametre est l'index dans le tableau de pipes du fd a conserver
 * si il est a -1 on efface tout
 * les second et troisiemes parametres indiquent si il faut supprimer le in, le
 * out, les deux ou aucun. 1 pour supprimer, 0 conserver
 * le troisieme parametre est la base, pour recuperer le tableau de pipes
 */
void	close_fds(int keep_open, int in, int out, t_base *base)
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
 * mettre actual_cmd->path_cmd a NULL et init des structures au depart 
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
		actual_cmd->path_cmd = check_cmd(base->path_list, act_tok->data);
		if (!actual_cmd->path_cmd)
		{
			ft_printf("Bash : Command '%s' not found\n", actual_cmd->cmd[0]);
			clean_exit(base, 127);
		}
		what_before(act_tok->prev, base);
		what_after(act_tok->next, base);
		execve(actual_cmd->path_cmd, actual_cmd->cmd, environ);
		if (errno)
			clean_exit(base, errno);
		close_fds(1, 1, -1, base);
		clean_exit(base, 0);
	}
}
