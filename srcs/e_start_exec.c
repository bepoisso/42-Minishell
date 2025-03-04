#include "../includes/minishell.h"

/**Idem a what next mais dans l'autre sens
 * pipes geres reste infile outfile
 */
int	what_before(t_token *act_tok, t_base *base)
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
			ft_printf(BLUE"index %s: %d\n"RESET, actual->data, actual->index_pipe);
			return (dup2(base->pipes[actual->index_pipe][0], STDIN_FILENO)
			, close(base->pipes[actual->index_pipe][1])
			, cls_pipes(actual->index_pipe, 0, 1, base), 0);
		}
		actual = actual->prev;
	}
	return (0);
}

/**
 * check si il y une redirection avant la commande et gere les
 *  redirections et pipes si il y en as
 */
int	what_after(t_token *act_tok, t_base *base)
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
			ft_printf(GREEN"index %s: %d\n"RESET, actual->data, actual->index_pipe);
			return (dup2(base->pipes[actual->index_pipe][1], STDOUT_FILENO)
			, close(base->pipes[actual->index_pipe][0])
				, cls_pipes(actual->index_pipe, 1, 0, base), 0);
		}
		actual = actual->next;
	}
	cls_pipes(-1, 1, 1, base);
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
	int a, b;

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
			ft_printf("%s: Command not found\n", act_tok->data);
			clean_exit(base, 127);
		}
		a = what_before(act_tok->prev, base);
		b = what_after(act_tok->next, base);
		if (!a && !b)
		{
			ft_putstr_fd("child\n", 2);
			ft_putstr_fd(actual_cmd->cmd[0], 2);
			ft_putstr_fd("\n", 2);
			execve(actual_cmd->path_cmd, actual_cmd->cmd, environ);
		}
		/* if (actual_cmd->builtin)
			//handle_builtin();//fonction gestion builtin
		else
			execve(actual_cmd->path_cmd, actual_cmd->cmd, environ); */
	/* 	if (errno)
		clean_exit(base, errno); */
		cls_pipes(1, 1, -1, base);
		clean_exit(base, 0);
	}
}
