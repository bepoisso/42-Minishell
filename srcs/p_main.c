#include "../includes/parser.h"

int main(void)
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
		printf("Vous avex tapez : %s\n",input);
		free(input);
	}
	return (0);
}
