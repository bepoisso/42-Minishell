#include "../includes/minishell.h"

/**
 * wait_rings - Waits for all child processes to finish and updates
 *  the exit code.
 * @base: Pointer to the base structure containing the count of forks
 *  and exit code.
 *
 * This function waits for all child processes to finish by calling waitpid
 *  in a loop.
 * It decrements the count of forks each time a child process finishes and
 *  updates exit code in the base structure based on the status of the finished
 *  process.
 *
 * Return: Always returns 0.
 */
/* int	wait_rings(t_base *base)
{
	int		status;
	int		i;
	int		sig;
	pid_t	pid;

	status = 0;
	i = 0;
	while(i < base->count_forks)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (pid == base->lastpid)
				base->exit_code = WEXITSTATUS(status);
			ft_putstr_fd(BLUE"exit code:"RESET, 2);
			ft_putnbr_fd(base->exit_code, 2);
			ft_putchar_fd('\n', 2);
			i++;
		}
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGPIPE)
			{
				ft_putstr_fd("\nBye (SIGPIPE detected)! in ", 2);
				ft_putnbr_fd(pid, 2);
				ft_putstr_fd("\n", 2);
			}
			i++;
		}
	}
	free_base(base);
	return (0);
} */

int	wait_rings(t_base *base)
{
	int		status;
	int		i;
	pid_t	pid;

	status = 0;
	i = 0;
	while (i < base->count_forks)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == base->lastpid)
			base->exit_code = WEXITSTATUS(status);
		i++;
	}
	return (0);
}

/**
 * fonction qui compte les forks pour permettre a sauron d'attendre tous les
 *  processus enfant a l'aide d'une boucle et de la fonction waitpid(-1) qui va
 *  decrementer le compteur base->count_forks jusqu'a 0
 */
int	count_forks(t_base *base)
{
	t_token	*tokcpy;

	tokcpy = base->token;
	while (tokcpy)
	{
		if (tokcpy->id == 9 && tokcpy->cmd->builtin == false)
			base->count_forks ++;
		tokcpy = tokcpy->next;
	}
	return (base->count_forks);
}

static void	error_handle(int type, char *cmd)
{
	char	*err;

	err = NULL;
	if (type == 1)
		err = error_message(RED"Command '", cmd
			, "' not found, but can be installed with:\n\tsudo apt install "
			, cmd, "\n"RESET, NULL);
	else if (type == 2)
		err = error_message(RED"Minishell: ", cmd
			, ": No such file or directory\n"RESET, NULL);
	else if (type == 3)
		err = error_message(RED"Minishell: ", cmd
		, ": Permission denied\n"RESET, NULL);
	ft_putstr_fd(err, 2);
	free_null((void **)&err);
}

static char	*is_absolute(t_token *actual, t_base *base)
{
	int	error;

	if (access(actual->cmd->cmd[0], X_OK) == 0)
		return (actual->cmd->cmd[0]);
	error = errno;
	if (error == ENOENT)
	{
		error_handle(2, actual->cmd->cmd[0]);
		base->exit_code = 127;
	}
	else if (error == EACCES)
	{
		error_handle(3, actual->cmd->cmd[0]);
		base->exit_code = 126;
	}
	return (NULL);
}

char	*check_cmd(t_token *actual, t_base *base)
{
	char	*path;
	char	**env_listcpy;

	if (ft_strchr(actual->cmd->cmd[0], '/'))
		return (is_absolute(actual, base));
	env_listcpy = base->path_list;
	path = NULL;
	if (env_listcpy)
	{
		while (*env_listcpy)
		{
			path = ft_strjoin(*env_listcpy, actual->cmd->cmd[0]);
			if (access(path, X_OK) == 0)
				return (base->exit_code = 0, path);
			if (errno == EACCES)
				(base->exit_code = 126, error_handle(3, actual->cmd->cmd[0]));
			free_null((void *)&path);
			env_listcpy++;
		}
		base->exit_code = 127;
		return (error_handle(1, actual->cmd->cmd[0]), NULL);
	}
	base->exit_code = 127;
	return (error_handle(2, actual->cmd->cmd[0]), NULL);
}
