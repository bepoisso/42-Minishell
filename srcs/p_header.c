#include "../includes/minishell.h"

void	delay(long time)
{
	long	delay;

	delay = 0;
	while (delay < time)
		delay++;
}

void	exec_clear(void)
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
}

void	print_delay(char *s, long time)
{
	long	delay;

	while (*s)
	{
		delay = 0;
		while (delay < time)
			delay++;
		ft_putchar(*s);
		s++;
	}
}

void	ascii(void)
{
	print_delay(VIOLET"   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       \n", DELAY_TIME);
	print_delay(" ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       \n", DELAY_TIME);
	print_delay(" ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       \n", DELAY_TIME);
	print_delay(" ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       \n", DELAY_TIME);
	print_delay(" ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       \n", DELAY_TIME);
	print_delay(" ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       \n", DELAY_TIME);
	print_delay(" ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ \n", DELAY_TIME);
	print_delay("  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ \n", DELAY_TIME);
	print_delay("            (° ͜ʖ͡°)╭∩╮                                                         ▀         ▀         \n"RESET, DELAY_TIME);
	print_delay(YELLOW"                                                              By bepoisso 🐟 & jrinaudo 🧌        \n"RESET, DELAY_TIME);
}

void	header(void)
{
	exec_clear();
	ft_putstr("Loading : ");
	print_delay(BLUE"█████", DELAY_DOT);
	print_delay("█", DELAY_DOT * 5);
	print_delay("███", DELAY_DOT);
	print_delay("███████", DELAY_DOT * 2);
	print_delay("██", DELAY_DOT);
	print_delay("██", DELAY_DOT / 2);
	print_delay("███"RESET, DELAY_DOT / 5);
	exec_clear();
	ascii();
}
