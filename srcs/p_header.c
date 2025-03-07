#include "../includes/minishell.h"

void	ascii(void)
{
	printf(VIOLET"   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       \n");
	printf(" ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       \n");
	printf(" ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       \n");
	printf(" ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       \n");
	printf(" ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       \n");
	printf(" ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       \n");
	printf(" ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ \n");
	printf("  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ \n");
	printf("                                                                              ▀         ▀         \n"RESET);
	printf(YELLOW"                                                              By bepoisso 🐟 & jrinaudo 😈        \n"RESET);
}

void	header(void)
{
	char		*argv[2];
	pid_t		pid;
	extern char	**environ;

	argv[0] = "clear";
	argv[1] = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		execve("/usr/bin/clear", argv, environ);
		write(2, "e\n", 2);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	ascii();
}