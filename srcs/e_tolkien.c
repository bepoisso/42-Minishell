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

static int	cmd_before(t_token *act_tok, int fd)
{
	t_token	*actual;

	actual = act_tok;
	while (actual)
	{
		if (actual->id == 9)
			actual->cmd->output = fd;
		actual = actual->prev;
	}
	return (0);
}

static int	cmd_after(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok;
	while (actual)
	{
		if (actual->id == 9)
			actual->cmd->input = fd;
		actual = actual->next;
	}
	return (0);
}
/* if (actual->id >= 3 && actual->id <= 6)
{
	if (file_redir(actual, base))
		return (1);
	return (0);
}	 */

static void	create_redir(t_base *base)
{
	t_token	*actual;
	int		pipeline[2];

	actual = base->token;
	while (actual)
	{
		if (actual->id == 7)
		{
			if (pipe(pipeline) < 0)
				exit(1);
			cmd_before(actual, pipeline[1]);
			cmd_after(actual, pipeline[0]);
		}
		actual = actual->next;
	}
}

static void	handle_cmd(t_token *tok, t_base *base)
{
	t_token	*actual;
	t_cmd	*actual_cmd;

	actual = tok;
	actual_cmd = base->cmds;
	while (actual)
	{
		if (actual->id == 9)
		{
			actual->cmd = actual_cmd;
			actual->cmd->input = 0;
			actual->cmd->output = 1;
			actual->cmd->pid = 0;
			actual_cmd = actual_cmd->next;
		}
		else
			actual->cmd = NULL;
		actual = actual->next;
	}
}

int	sauron(t_base *base)
{
	t_token	*tok;

	tok = base->token;
	handle_cmd(tok, base);
	create_redir(base);
	base->count_forks = count_forks(base);
	base->path_list = extract_paths();
	while (tok)
	{
	/* 	if (tok->id == 8)
			handle_env(actual_cmd, tok, base); */

		
		if (tok && tok->id == 9)
		{
			prepare_exec(tok, base);
		}
		tok = tok->next;
	}
	wait_rings(base);
	return (0); 
}
