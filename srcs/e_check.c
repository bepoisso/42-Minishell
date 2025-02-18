#include "../includes/minishell.h"

int	file_check(char *file, int type, t_base base)
{
	int fd;

	if (type == 1)
	{
		fd = open(file, O_RDONLY);
		{
			if (errno == ENOENT)
			{
				return (ft_error("No such file or directory\n", 1, base), 1); //A TERMINER
			}
		}
	}
	else if (type == 2)
		fd = open(file, O_CREAT);
	if (fd == -1 && errno == EACCES)
		{
			perror("Permission denied\n");
			return (ft_error("", 1, base), 1); // A TERMINER TROUVER CODE ERREUR BASH RENVOI 1 teste avec $?
		}
	return (0);
}

#include <stdio.h>
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
}