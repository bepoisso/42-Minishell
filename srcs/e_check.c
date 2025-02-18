#include "../includes/minishell.h"

/**
 * @brief Checks the existence and accessibility of a file.
 *
 * This function attempts to open a file based on the specified type and
 *  checks for errors.
 * If the file cannot be opened due to it not existing or due to permission issues, appropriate
 * error messages are displayed and an error code is returned.
 *
 * @param file The path to the file to be checked.
 * @param type The type of check to be performed:
 *             - 1: Check if the file exists and can be opened for reading.
 *             - 2: Check if the file can be created.
 * @param base The base structure containing necessary context for error handling.
 *
 * @return int Returns 0 if the file check is successful, or 1 if an error occurs.
 */
int	file_check(char *file, int type, t_base base)
{
	int fd;

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
		fprintf(stderr, "Type 1: lecture uniquement, Type 2: création (ouverture en écriture)\n");
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