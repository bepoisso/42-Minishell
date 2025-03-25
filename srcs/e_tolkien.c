#include "../includes/minishell.h"

/*FONCTION SAURON
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		>>		redir outfile append
7		|		pipe
8		$		variable
9		cmd		commande
10		args	commande args */
int	is_last_cmd(pid_t pid, t_cmd *actual)
{
	t_cmd	*cmd;

	cmd = actual;
	while (actual)
	{
		if (actual->last_cmd == 1 && actual->pid == pid)
			return (1);
		actual = actual->next;
	}
	return (0);
}

static int	wait_rings(t_base *base)
{
	int		status;
	int		i;
	pid_t	pid;

	status = 0;
	i = 0;
	while (i < base->count_forks)
	{
		pid = waitpid(-1, &status, 0);
		if (is_last_cmd(pid, base->cmds))
			base->exit_code = WEXITSTATUS(status);
		i++;
	}
	return (0);
}

static int	cmd_found_exec(t_base *base, t_token *tok, int cmd_found)
{
	prepare_exec(tok, base);
	cmd_found++;
	return (cmd_found);
}

void	sauron(t_base *base, int cmd_found, int redir_found)
{
	t_token	*tok;
	t_token	*tok_back;

	tok = base->token;
	init_exec(base);
	while (tok)
	{
		tok_back = tok;
		while (tok && tok->id != 7)
		{
			if (tok->id == 9)
				cmd_found = cmd_found_exec(base, tok, cmd_found);
			else if (tok->id >= 3 && tok->id <= 6)
				redir_found ++;
			tok = tok->next;
		}
		if (redir_found > 0 && cmd_found == 0)
			handle_redirec_alone(tok_back);
		if (tok)
			tok = tok->next;
		tok_back = tok;
	}
	wait_rings(base);
	add_history(base->input);
	free_base(base);
}
