#include "../includes/minishell.h"
/**
 * La variable environ est définie et initialisée dans la bibliothèque C (libc).
 * Elle est automatiquement configurée par le système lors du démarrage de votre
 * programme pour contenir l'ensemble des variables d'environnement du processus
 * en cours.
 */
/* int main(int argc, char **argv)
{
	(void)argv;
	extern char **environ;
	char **str = environ;
	while(*str)
	{
		printf("%s\n", *str);
		str++;
	}
	return (argc);
} */

void	free_null(void	**ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_doubletab(char ***str)
{
	char	**temp;

	if (str && *str)
	{
		temp = *str;
		while (*temp)
		{
			free_null((void **)temp);
			temp++;
		}
		free_null((void **)str);
	}
}

char	**extract_pass(char *cmd)
{
	char	*env;
	char	**env_list;
	char	**env_listcpy;
	(void)	cmd;
	env = getenv("PATH");
	if (!env)
		return (NULL);
	env_list = ft_split(env, ':');
	if (!env_list)
		return (free_null((void *)&env), NULL);
	env_listcpy = env_list;
	while (*env_listcpy)
	{
		*env_listcpy = ft_strjoin(*env_listcpy, "/");
		if (!env_listcpy)
			return (free_doubletab(&env_list), free_null((void *)&env), NULL);
		printf("%s", *env_listcpy);
		env_listcpy++;
	}
	return (env_list);
}

/**
 * execution de la commande ls 
 */
int main(int argc, char **argv)
{
	(void)argv;
	extern char **environ;
	int	status = 0;
	pid_t	pid;
	char *
	
	
	extract_pass(argv[1]);
	pid = fork();
	if (pid == -1)
		perror("Error fork");
	else if (pid == 0)
	{
		printf("deput du process fils");
		execve("/bin/ls", argv + 1, environ);
	}
	else if (pid > 0)
		waitpid(-1, &status, 0);
	printf("retour dans le pere");
	return (argc);
}