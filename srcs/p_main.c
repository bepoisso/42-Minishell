#include "../includes/minishell.h"

int main(int ac, char **av)
{
	char	*input;
	t_base	base;

	(void)ac;
	(void)av;
	ft_memset(&base, 0, sizeof(t_base));
	header();
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
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
		print_tokens(base.token);
		printf("\n\n\n");
		print_cmd(&base);
		sauron(&base);
		free(input);
	}
	return (0);
}