#include "../includes/minishell.h"

//ls -la | grep dr | sort | rev > outfile

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
	if (actual->cmd->input > 0)
	{
		dup2(actual->cmd->input, STDIN_FILENO);
		if (actual->cmd->input < 0)
			return (ft_error("dup2 failed", 1, actual->base));
		close(actual->cmd->input);
	}
	if (actual->cmd->output > 1)
	{
		dup2(actual->cmd->output, STDOUT_FILENO);
		if (actual->cmd->output < 0)
			return (ft_error("dup2 failed", 1, actual->base));
		close(actual->cmd->output);
	}
}

static void	exec_redir_main_process(t_token *actual)
{
	if (actual->cmd->output > 1)
	{
		actual->base->stdout_back = dup(STDOUT_FILENO);
		if (actual->base->stdout_back < 0)
			return (ft_error("dup2 failed", 1, actual->base));
		dup2(actual->cmd->output, STDOUT_FILENO);
		if (actual->cmd->output < 0)
			return (ft_error("dup2 failed", 1, actual->base));
		close(actual->cmd->output);
	}
}

int	prepare_exec(t_token *actual, t_base *base)
{
	if (handle_redirections(actual, base, actual->cmd))
		return (close_inpt_outp(actual->cmd), base->exit_code = 1);
	if (actual->cmd->builtin)
	{
		exec_redir_main_process(actual);
		base->exit_code = exec_builtins(actual);
		close_opend_fds_builtins(actual->cmd, base);
	}
	else
	{
		base->lastpid = fork();
		if (base->lastpid == -1)
			return (perror("Error: create fork\n"), clean_exit(base), 1);
		if (base->lastpid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			exec_redir(actual);
			close_fds(base, actual->cmd);
			actual->cmd->path_cmd = check_cmd(actual, base);
			if (!actual->cmd->path_cmd)
			return (close(actual->cmd->input), close(actual->cmd->output)
			, clean_exit(base), 1);
			execve(actual->cmd->path_cmd, actual->cmd->cmd, base->env);
			base->exit_code = errno;
			clean_exit(base);
		}
		close_inpt_outp(actual->cmd);
	}
	return (0);
}
