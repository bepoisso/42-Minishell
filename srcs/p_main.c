#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		printf("Vous avex tapez : %s\n",input);
		free(input);
	}
	return (0);
}
