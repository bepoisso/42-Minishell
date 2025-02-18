
#include "../includes/minishell.h"

/**
 * Checks if a command exists in the PATH environment variable
 * and returns the full path to the command if found.
 *
 * @param env_list Array of possible paths to search in
 * @param cmd Command to search for
 *
 * @return Full path to the command if found and executable,
 *         NULL if command not found or not executable.
 *         Prints "command not found" to stdout if command not found.
 *
 * @note Dynamically allocates memory for the path string.
 *       Caller must free the returned string when no longer needed.
 */
static char	*check_cmd(char **env_list, char *cmd)
{
	char	*path;
	char	**env_listcpy;

	env_listcpy = env_list;
	while (*env_listcpy)
	{
		path = ft_strjoin(*env_listcpy, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free_null((void *)&path);
		env_listcpy++;
	}
	ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

/**
 * @brief Extracts and formats PATH environment variable into an array of paths
 * 
 * This function gets the PATH environment variable, splits it into individual
 *  paths,
 * and adds a trailing slash to each path.
 * 
 * @return char** Array of paths with trailing slashes, NULL if:
 *                - PATH environment variable is not found
 *                - Memory allocation fails
 *                - Split operation fails
 * 
 * @note The returned array must be freed by the caller
 * @note Each path in the returned array ends with a '/' character
 */
char	**extract_paths(void)
{
	char	*env;
	char	**env_list;
	char	*env_listcpy;
	int		i;

	i = 0;
	env_list = NULL;
	env_listcpy = NULL;
	env = getenv("PATH");
	if (!env)
		return (NULL);
	env_list = ft_split(env, ':');
	if (!env_list)
		return (NULL);
	while (env_list[i])
	{
		env_listcpy = ft_strjoin(env_list[i], "/");
		if (!env_listcpy)
			return (free_doubletab(&env_list), NULL);
		free_null((void *)&env_list[i]);
		env_list[i] = env_listcpy;
		i++;
	}
	return (env_list);
}

/**
 * @brief Executes a command in a child process
 *
 * Creates a child process using fork() and executes the specified command
 * using execve(). The parent process waits for the child to complete.
 * La variable environ est définie et initialisée dans la bibliothèque C (libc).
 * Elle est automatiquement configurée par le système lors du démarrage de votre
 * programme pour contenir l'ensemble des variables d'environnement du processus
 * en cours.
 * @param path The full path to the executable
 * @param cmd Array of strings containing the command and its arguments
 * @return Returns 0 on successful execution, -1 on fork failure
 *
 * @note Uses the global environ variable for environment variables
 * @note Parent process waits for any child process to terminate
 *  (waitpid with -1)
 */
static int	exec_cmd(char *path, char **cmd)
{
	extern char	**environ;
	int			status;
	pid_t		pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("Error fork");
	else if (pid == 0)
		execve(path, cmd, environ);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

/**
 * @brief Main function that handles command execution process
 *
 * This function manages the execution flow of commands by:
 * 1. Extracting PATH environment variable
 * 2. Checking if command exists in PATH
 * 3. Executing the command if found
 *
 * @param argc Number of arguments (unused)
 * @param argv Array of command line arguments where argv[1] is
 *  the command to execute
 * @return int Returns:
 *         - 0 on successful execution
 *         - 1 if path extraction fails or command is not found
 */
int	start_exec_cmd(t_cmd *cmd)
{
	char	**cmd_path;

	cmd_path = NULL;
	cmd_path = extract_paths();
	if (!cmd_path)
		return (1);
	cmd->path_cmd = check_cmd(cmd_path, cmd->cmd[0]);
	if (!cmd->path_cmd)
		return (free_doubletab(&cmd_path), 1); //AJOUT GESTION ERREUR
	exec_cmd(cmd->path_cmd, cmd->cmd);
	free_null((void *)&cmd->path_cmd);
	free_doubletab(&cmd_path);
	return (0);
}
/*valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
 --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup
  ./minishell pwd */

/* int	main(int argc, char **argv)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (1);
	command->cmd = malloc(sizeof(char *) * 3);
	if (!command->cmd)
	{
		free(command);
		return (1);
	}
	if (argc < 2)
	{
		free(command->cmd);
		free(command);
		return (write(2, "NO ARGS\n", 8));
	}
	command->cmd[0] = ft_strdup(argv[1]);
	command->cmd[1] = argc > 2 ? ft_strdup(argv[2]) : NULL;
	command->cmd[2] = NULL;
	start_exec_cmd(command);
	free(command->cmd[0]);
	if (command->cmd[1])
		free(command->cmd[1]);
	free(command->cmd);
	free(command);
	return (0);
} */
