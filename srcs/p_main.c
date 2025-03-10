#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	t_base	base;

	ft_memset(&base, 0, sizeof(t_base));
	input = 0;
	header();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (ft_printf("exit\n"), 0);
		if (input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			continue;
		}
		add_history(input);
		if (parser(input, &base))
			break;
		identify_token(&base);
		print_tokens(base.token);
		base.token = token_parser(base.token);
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
 		printf("-----------------------------------------\n");
 		print_tokens(base.token);
		printf("\n\n\n");
		print_cmd(&base);
		printf("-----------------------------------------\n\n");
		sauron(&base);
		free(input);
	}
	return (0);
}