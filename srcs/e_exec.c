
#include "../includes/minishell.h"

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
static char	*check_cmd(char **env_list, t_base *base)
{
	char	*path;
	char	**env_listcpy;

	env_listcpy = env_list;
	while (*env_listcpy)
	{
		path = ft_strjoin(*env_listcpy, base->cmds->cmd[0]);
		if (access(path, X_OK) == 0)
			return (path);
		free_null((void *)&path);
		env_listcpy++;
	}
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
 * @brief Executes a base in a child process
 *
 * Creates a child process using fork() and executes the specified base
 * using execve(). The parent process waits for the child to complete.
 * La variable environ est définie et initialisée dans la bibliothèque C (libc).
 * Elle est automatiquement configurée par le système lors du démarrage de votre
 * programme pour contenir l'ensemble des variables d'environnement du processus
 * en cours.
 * @param path The full path to the executable
 * @param cmd Array of strings containing the base and its arguments
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
 * @brief Starts the execution of a base.
 *
 * This function extracts the paths, checks the base, and executes it.
 * It also handles the necessary memory management for the base paths.
 *
 * @param cmd A pointer to the base structure containing the base to be executed.
 * 
 * @return Returns 0 on success, or 1 on failure.
 */
int	start_exec_cmd(t_base *base)
{
	char	**cmd_path;

	cmd_path = NULL;
	cmd_path = extract_paths();
	if (!cmd_path)
		return (1);
	base->cmds->path_cmd = check_cmd(cmd_path, base);
	if (!base->cmds->path_cmd)
		return (ft_error("bash: basee: base not found\n", 127, *base), free_doubletab(&cmd_path), 127);
	exec_cmd(base->cmds->path_cmd, base->cmds);
	free_null((void *)&base->cmds->path_cmd);
	free_doubletab(&cmd_path);
	return (0);
}
/*valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
 --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup
  ./minishell pwd */

int	main(int argc, char **argv)
{
	t_base	*base;

	base = malloc(sizeof(t_base));
	if (!base)
		return (1);
	base->cmds = malloc(sizeof(t_cmd));
	if (!base->cmds)
	{
		free(base);
		return (1);
	}
	base->cmds->cmd = malloc(sizeof(char *) * 2);
	if (!base->cmds->cmd)
	{
		free(base);
		return (1);
	}
	if (argc < 2)
	{
		free(base->cmds->cmd);
		free(base);
		return (write(2, "NO ARGS\n", 8));
	}
	base->cmds->cmd[0] = ft_strdup(argv[1]);
	//base->cmds->cmd[1] = argc > 2 ? ft_strdup(argv[2]) : NULL;
	base->cmds->cmd[1] = NULL;
	start_exec_cmd(base);
	free(base->cmds->cmd[0]);
	if (base->cmds->cmd[1])
		free(base->cmds->cmd[1]);
	free(base->cmds->cmd);
	free(base);
	return (0);
}
