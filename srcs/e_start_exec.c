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
	while (actual->next && actual->next->id != 7)
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

/**
 * act_cmd->path_cmd A FREE A LA FIN !!!!!!
 * gestion des erreurs a faire
 * CHANGER POUR FONCTION QUI PRINT DANS FD2
 */
int	prepare_exec(t_token *tok, t_base *base, t_cmd *actcmd)
{
	extern char	**environ;
	t_token		*actual;

	actual = tok;
	if (handle_redirections(actual, base, actcmd))
		return (1);
	actcmd->pid = fork();
	if (actcmd->pid == -1)
	{
		perror("Error: create fork\n");
		clean_exit(base, -1);
	}
	if (actcmd->pid == 0)
	{
		if (actcmd->input != 0)
		{
			if (!base->exit_code)
				dup2(actcmd->input, STDIN_FILENO);
			close(actcmd->input);
		}
		if (actcmd->output != 1)
		{
			dup2(actcmd->output, STDOUT_FILENO);
			close(actcmd->output);
		}
		close_fds(base, actcmd);
		if (ft_strcmp(actcmd->cmd[0], "ls"))
			close(STDIN_FILENO);
		actcmd->path_cmd = check_cmd(base->path_list, actcmd->cmd[0], base);
		if (!actcmd->path_cmd)
		{
				close(actcmd->input);
				close(actcmd->output);
			return (clean_exit(base, 127), 1);
		}
		if (base->exit_code != 127)
			execve(actcmd->path_cmd, actcmd->cmd, environ);
		if (actcmd->input != 0)
			close(actcmd->input);
		if (actcmd->output != 1)
			close(actcmd->output);
		base->exit_code = errno;
		clean_exit(base, base->exit_code);
	}
	else
	{
		ft_putstr_fd(BLUE"PID exec:[", 2);
		ft_putstr_fd(actcmd->cmd[0], 2);
		ft_putstr_fd("] ", 2);
		ft_putnbr_fd(actcmd->pid, 2);
		ft_putstr_fd(RESET"\n", 2);

		if (actcmd->input != 0)
			close(actcmd->input);
		if (actcmd->output != 1)
			close(actcmd->output);
	}
	return (0);
}
