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
char	*check_cmd(char **env_list, t_cmd *cmd)
{
	char	*path;
	char	**env_listcpy;

	env_listcpy = env_list;
	while (*env_listcpy)
	{
		path = ft_strjoin(*env_listcpy, cmd->cmd[0]);
		if (access(path, X_OK) == 0)
			return (path);
		free_null((void *)&path);
		env_listcpy++;
	}
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
int	file_check(char *file, int type, t_base *base)
{
	int	fd;

	if (type == 1)
	{
		fd = open(file, O_RDONLY);
		{
			if (errno == ENOENT)
				return (ft_error("No such file or directory\n", 1, base), 1);
		}
	}
	else if (type == 2)
		fd = open(file, O_CREAT);
	if (fd == -1 && errno == EACCES)
	{
		perror("Permission denied\n");
		return (ft_error("", 1, base), 1);
	}
	return (0);
}

/* #include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	t_base base;

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <nom_du_fichier> <type>\n", argv[0]);
		fprintf(stderr, "Type 1: lecture uniquement, Type 2: création
		 (ouverture en écriture)\n");
		return (1);
	}

	int type = atoi(argv[2]);
	int ret = file_check(argv[1], type, base);

	if (ret == 0)
		printf("Vérification du fichier réussie.\n");
	else
		printf("Échec de la vérification du fichier (code %d).\n", ret);

	return (ret);
} */