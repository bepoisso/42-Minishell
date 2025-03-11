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

static int	cmd_before(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok->prev;
	while (actual && actual->id != 7)
	{
		if (actual->id == 9)
		{
			actual->cmd->output = fd;
		}
		actual = actual->prev;
	}
	return (0);
}

static int	cmd_after(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok->next;
	while (actual && actual->id != 7)
	{
		if (actual->id == 9)
		{
			actual->cmd->input = fd;
		}
		actual = actual->next;
	}
	return (0);
}

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
			actual->cmd->hrdoc = 0;
			actual_cmd = actual_cmd->next;
		}
		else
			actual->cmd = NULL;
		actual = actual->next;
	}
}


int	sauron(t_base *base)
{
	t_token				*tok;

	tok = base->token;
	handle_cmd(tok, base);
	create_redir(base);
	base->count_forks = count_forks(base);
	base->path_list = extract_paths();
	while (tok)
	{
	/* 	if (tok->id == 8)
			handle_env(actual_cmd, tok, base); */
		if (tok->id == 9 && tok->cmd->builtin == true)
			handling_builtin(base, tok);
		else if (tok->id == 9)
			prepare_exec(tok, base);
/* 		if (tok->id == 9 && tok->cmd->builtin == 1)
			handle_env(tok, base); */
		tok = tok->next;
	}
	wait_rings(base);
	printf(BLUE"Exit Code in Sauron : %d\n"RESET, base->exit_code);
	return (0);
}
