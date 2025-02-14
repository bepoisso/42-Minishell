
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
	printf("command not found\n");
	return (NULL);
}

/**
 * @brief Extracts and formats PATH environment variable into an array of paths
 * 
 * This function gets the PATH environment variable, splits it into individual paths,
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
 * @note Parent process waits for any child process to terminate (waitpid with -1)
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
 * @param argv Array of command line arguments where argv[1] is the command to execute
 * @return int Returns:
 *         - 0 on successful execution
 *         - 1 if path extraction fails or command is not found
 */
int	main(int argc, char **argv)
{
	char	**cmd_path;
	char	*full_path;

	(void)argc;
	cmd_path = NULL;
	full_path = NULL;
	cmd_path = extract_paths();
	if (!cmd_path)
		return (1);
	full_path = check_cmd(cmd_path, argv[1]);
	if (!full_path)
		return (free_doubletab(&cmd_path), 1);
	exec_cmd(full_path, &argv[1]);
	free_null((void *)&full_path);
	free_doubletab(&cmd_path);
	return (0);
}
/*valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
 --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup
  ./minishell pwd */