#include "../includes/minishell.h"

static void	handle_in_out(t_cmd *cmd, t_token *actual)
{
	t_base	*base;

	base = actual->base;
	if (actual->id == 3 || actual->id == 5)
	{
		if (cmd->input > 0)
			close(cmd->input);
		cmd->input = filechk(actual->next, actual->id, base, cmd);
		if (cmd->input == -1)
			cmd->bad_fd = 1;
	}
	else if (actual->id == 4 || actual->id == 6)
	{
		if (cmd->output > 2)
			close(cmd->output);
		cmd->output = filechk(actual->next, actual->id, base, cmd);
		if (cmd->input == -1)
			cmd->bad_fd = 1;
	}
}

int	handle_redirections(t_token *token, t_cmd *cmd)
{
	t_token	*actual;

	actual = token;
	while (actual->prev && actual->prev->id != 7)
		actual = actual->prev;
	while (actual && actual->id != 7)
	{
		handle_in_out(cmd, actual);
		actual = actual->next;
	}
	if (cmd->bad_fd == 1)
		return (-1);
	return (0);
}

void	close_inpt_outp(t_cmd *actualcmd)
{
	if (actualcmd->input > 2 && (actualcmd->hrdoc != actualcmd->input))
	{
		close(actualcmd->input);
		actualcmd->input = 0;
	}
	if (actualcmd->output > 2)
	{
		close(actualcmd->output);
		actualcmd->output = 1;
	}
	if (actualcmd->hrdoc > 2)
	{
		close(actualcmd->hrdoc);
		actualcmd->hrdoc = 0;
	}
}

static void	raz_std_fds(t_base *base)
{
	if (base->stdout_back)
	{
		if (dup2(base->stdout_back, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(base->stdout_back);
		base->stdout_back = 0;
	}
	if (base->stdin_back)
	{
		if (dup2(base->stdin_back, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(base->stdin_back);
		base->stdin_back = 0;
	}
}

void	close_opend_fds_builtins(t_cmd *actualcmd, t_base *base)
{
	if (actualcmd->input > 2 && (actualcmd->hrdoc != actualcmd->input))
	{
		close(actualcmd->input);
		actualcmd->input = 0;
	}
	if (actualcmd->output > 2)
	{
		close(actualcmd->output);
		actualcmd->output = 1;
	}
	if (actualcmd->hrdoc > 2)
	{
		close(actualcmd->hrdoc);
		actualcmd->hrdoc = 0;
	}
	raz_std_fds(base);
}
