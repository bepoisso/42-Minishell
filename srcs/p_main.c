#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	t_base	base;

	(void)ac;
	(void)av;
	ft_memset(&base, 0, sizeof(t_base));
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
		parser(input, &base);
		identify_token(&base);
		// create_base()
		// exec();
		print_tokens(base.token);
		free(input);
	}
	return (0);
}
