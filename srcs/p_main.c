#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	t_base	*base;
	t_token	*tokens;


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
		tokens = parser(input, env);
		// create_base()
		// exec();
		free(input);
	}
	return (0);
}
