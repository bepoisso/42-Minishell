#include "../includes/minishell.h"

//ls -la | grep dr | sort | rev > outfile
/**
 * @brief Handles the operations to be performed before executing a command.
 *
 * This function iterates through the tokens and performs necessary actions
 * based on the token's ID. It handles file redirections and pipe duplications.
 *at | 
 * @param actual Pointer to the current token.
 * @param base Pointer to the base structure containing pipe information.
 * @return int Returns 1 if there is an error in file redirection, otherwise 0.
 */

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
			if (cmd->input > 2)
				close(cmd->input);
			cmd->input = filechk(actual->next, actual->id, base);
			if (cmd->input < 0)
				return (-1);
		}
		else if (actual->id == 4 || actual->id == 6)
		{
			if (cmd->output > 2)
				close(cmd->output);
			cmd->output = filechk(actual->next, actual->id, base);
			if (cmd->output < 0)
				return (-1);
		}
		actual = actual->next;
	}
	return (0);
}

void	close_fds(t_base *base, t_cmd *actualcmd)
{
	t_cmd *cmd;

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
		else if (cmd == actualcmd)
		{
			if (cmd->input != 0)
			{
				dup2(cmd->input, STDIN_FILENO);
				close(cmd->input);
			}
			if (cmd->output != 1)
			{
				dup2(cmd->output, STDOUT_FILENO);
				close(cmd->output);
			}
		}
		cmd = cmd->next;
	}
}

int	prepare_exec(t_token *actual, t_base *base)
{
	extern char	**environ;

	if (handle_redirections(actual, base, actual->cmd))
		return (1);
	actual->cmd->pid = fork();
	if (actual->cmd->pid == -1)
	{
		perror("Error: create fork\n");
		clean_exit(base, -1);
	}
	if (actual->cmd->pid == 0)
	{
		//signal(SIGPIPE, SIG_IGN);
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
		close_fds(base, actual->cmd);
		actual->cmd->path_cmd = check_cmd(base->path_list, actual->data, base);
		if (!actual->cmd->path_cmd)
			return (close(actual->cmd->input), close(actual->cmd->output), clean_exit(base, 127), 1);
		execve(actual->cmd->path_cmd, actual->cmd->cmd, environ);
		base->exit_code = errno;
		clean_exit(base, base->exit_code);
	}
	else
	{
		if (actual->cmd->input != 0)
			close(actual->cmd->input);
		if (actual->cmd->output != 1)
			close(actual->cmd->output);
	}
	return (0);
}
