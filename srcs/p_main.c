#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	t_base	base;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
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
		{
			free(input);
			continue;
		}
		identify_token(&base);
		//print_tokens(base.token);
		base.token = token_parser(base.token);
		if (check_only_redirect(base.token, &base))
		{
			free(input);
			continue ;
		}
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
		if (ft_strcmp(base.token->data, "exit"))
			return (free(input), clean_exit(&base, 0), 0);
 	/* 	printf("-----------------------------------------\n");
 		print_tokens(base.token);
		printf("\n\n\n");
		print_cmd(&base);
		printf("-----------------------------------------\n\n"); */
		sauron(&base);
		free_base(&base);
		printf(GREEN"Exit Code in main : %d\n"RESET, base.exit_code);
		free(input);
	}
	return (0);
}
