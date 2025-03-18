#include "../includes/minishell.h"

//ls -la | grep dr | sort | rev > outfile
static int	handle_redirections(t_token *token, t_base *base, t_cmd *cmd)
{
	t_token	*actual;

	actual = token;
	while (actual->prev && actual->prev->id != 7)
		actual = actual->prev;
	while (actual && actual->id != 7)
	{
		if (actual->id == 3 || actual->id == 5)
		{
			if (cmd->input > 0)
				close(cmd->input);
			cmd->input = filechk(actual->next, actual->id, base, cmd);
		}
		else if (actual->id == 4 || actual->id == 6)
		{
			if (cmd->output > 2)
				close(cmd->output);
			cmd->output = filechk(actual->next, actual->id, base, cmd);
		}
		if (cmd->input < 0 || cmd->output < 0)
			return (-1);
		actual = actual->next;
	}
	return (0);
}

static void	close_inpt_outp(t_cmd *actualcmd)
{
	if (actualcmd->input > 2)
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

void	close_fds(t_base *base, t_cmd *actualcmd)
{
	t_cmd	*cmd;

	cmd = base->cmds;
	while (cmd)
	{
		if (cmd != actualcmd)
		{
			if (cmd->input != 0)
				close(cmd->input);
			if (cmd->output != 1)
				close(cmd->output);
		}
		cmd = cmd->next;
	}
}

static void	exec_redir(t_token *actual)
{
	if (actual->cmd->input != 0)
	{
		dup2(actual->cmd->input, STDIN_FILENO);
		close(actual->cmd->input);
	}
	if (actual->cmd->output != 1)
	{
		dup2(actual->cmd->output, STDOUT_FILENO);
		close(actual->cmd->output);
	}
}

int	prepare_exec(t_token *actual, t_base *base)
{
	if (handle_redirections(actual, base, actual->cmd))
		return (close_inpt_outp(actual->cmd), base->exit_code = 1);
	if (actual->cmd->builtin)
	{
		exec_redir(actual);
		exec_builtins(actual);
	}
	else
	{
		base->lastpid = fork();
		if (base->lastpid == -1)
		return (perror("Error: create fork\n"), clean_exit(base, -1), 1);
		if (base->lastpid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			exec_redir(actual);
			close_fds(base, actual->cmd);
			actual->cmd->path_cmd = check_cmd(actual, base);
			if (!actual->cmd->path_cmd)
			return (close(actual->cmd->input), close(actual->cmd->output)
			, clean_exit(base, 127), 1);
			execve(actual->cmd->path_cmd, actual->cmd->cmd, base->env);
			base->exit_code = errno;
			clean_exit(base, base->exit_code);
		}
	}
	close_inpt_outp(actual->cmd);
	return (0);
}
