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
	while (actual && actual->id != 7)
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


/**
 * act_cmd->path_cmd A FREE A LA FIN !!!!!!
 * gestion des erreurs a faire
 * CHANGER POUR FONCTION QUI PRINT DANS FD2
 */
int	prepare_exec(t_token *actual, t_base *base)
{
	extern char	**environ;

	
	if (handle_redirections(actual->prev, base, actual->cmd))
		return (1);
	actual->cmd->path_cmd = check_cmd(base->path_list, actual->data, base);
	if (!actual->cmd->path_cmd)
		return (clean_exit(base, 127), 1);
	actual->cmd->pid = fork();
	if (actual->cmd->pid == -1)
	{
		perror("Error: create fork\n");
		clean_exit(base, -1);
	}
	if (actual->cmd->pid == 0)
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
		execve(actual->cmd->path_cmd, actual->cmd->cmd, environ);
		base->exit_code = errno;
		clean_exit(base, base->exit_code);
	}
	else
	{
		ft_putstr_fd(BLUE"PID exec: ", 2);
		ft_putnbr_fd(actual->cmd->pid, 2);
		ft_putstr_fd(RESET"\n", 2);
		if (actual->cmd->input != 0)
			close(actual->cmd->input);
		if (actual->cmd->output != 1)
			close(actual->cmd->output);
	}
	return (0);
}
