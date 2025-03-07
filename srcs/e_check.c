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
int	wait_rings(t_base *base)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while(i < base->count_forks)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			base->exit_code = WEXITSTATUS(status);
			i++;
		}
	}
	free_base(base);
	return (0);
}


/* int	wait_rings(t_base *base)
{
	int	status;

	status = 0;
	waitpid(base->pid_last, &status, 0);
	if (WIFEXITED(status))
		base->exit_code = WEXITSTATUS(status);
	free_base(base);
	return (0);
} */

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
		if (tokcpy->id == 9)
			base->count_forks ++;
		tokcpy = tokcpy->next;
	}
	return (base->count_forks);
}

/**
 * Checks if a base exists in the PATH environment variable
 * and returns the full path to the base if found.
 *
 * @param env_list Array of possible paths to search in
 * @param cmd base to search for
 *
 * @return Full path to the base if found and executable,
 *         NULL if base not found or not executable.
 *         Prints "base not found" to stdout if base not found.
 *
 * @note Dynamically allocates memory for the path string.
 *       Caller must free the returned string when no longer needed.
 */
char	*check_cmd(char **env_list, char *cmd, t_base *base)
{
	char	*path;
	char	**env_listcpy;

	env_listcpy = env_list;
	while (*env_listcpy)
	{
		path = ft_strjoin(*env_listcpy, cmd);
		if (access(path, X_OK) == 0)
			return (base->exit_code = 0, path);
		free_null((void *)&path);
		env_listcpy++;
	}
	base->exit_code = 127;
	ft_putstr_fd(RED"Command '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("' not found, but can be installed with:", 2);
	ft_putstr_fd("\nsudo apt install ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n"RESET, 2);
	return (NULL);
}

/**
 * @brief Checks the existence and accessibility of a file.
 *
 * This function attempts to open a file based on the specified type and
 *  checks for errors.
 * If the file cannot be opened due to it not existing or due to permission
 *  issues, appropriate
 * error messages are displayed and an error code is returned.
 *
 * @param file The path to the file to be checked.
 * @param type The type of check to be performed:
 *             - 1: Check if the file exists and can be opened for reading.
 *             - 2: Check if the file can be created.
 * @param base The base structure containing necessary context for error
 *  handling.
 *
 * @return int Returns 0 if the file check is successful, or 1 if an error
 *  occurs.
 */
int	filechk(t_token *token, int type, t_base *base)
{
	int		fd;
	char	*file;

	if (token)
		file = token->data;
	else
		return (ft_error("bash: syntax error near unexpected token\n", 1, base)
			, -1);
	fd = 0;
	if (type == 3)
		fd = open(file, O_RDONLY);
	//if (type == 5)
		//fd = heredoc(base);A FAIRE
	else if (type == 4)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 6)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && errno == EACCES)
		return (perror("Permission denied\n"), ft_error("", 1, base), -1);
	if (fd == -1 && errno == ENOENT)
		return (ft_error("No such file or directory\n", 1, base), -1);
	return (fd);
}
