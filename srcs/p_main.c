#include "../includes/parser.h"

int main(int ac, char **av, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("mini$ell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		parser(input, env);
		free(input);
	}
	return (0);
}
