#include "../includes/minishell.h"

static int	cmd_before(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok->prev;
	while (actual && actual->id != 7)
	{
		if (actual->id == 9)
		{
			actual->cmd->output = fd;
			return (0);
		}
		actual = actual->prev;
	}
	close(fd);
	return (1);
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
			return (0);
		}
		actual = actual->next;
	}
	close(fd);
	return (1);
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
			if (actual_cmd->next == NULL)
				actual_cmd->last_cmd = 1;
			actual_cmd = actual_cmd->next;
		}
		else
			actual->cmd = NULL;
		actual = actual->next;
	}
}

void	init_exec(t_base *base)
{
	handle_cmd(base->token, base);
	create_redir(base);
	base->count_forks = count_forks(base);
	base->path_list = extract_paths(base);
}
