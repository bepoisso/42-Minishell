#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	t_base	base;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&base, 0, sizeof(t_base));
	input = NULL;
	header();
	base.env = env_cpy();
	while (1)
	{
		input = readline("🤏🐚> ");
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
		identify_token(base.token);
		print_tokens(base.token);
		base.token = token_parser(base.token);
		if (check_only_redirect(base.token, &base))
		{
			free(input);
			continue ;
		}
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
		if (ft_strcmp(base.token->data, "exit") && !base.token->next)
			return (free(input), clean_exit(&base, 0), 0);
/*  		ft_printf("-----------------------------------------\n");
 		print_tokens(base.token);
		ft_printf("\n\n\n");
		print_cmd(&base);
		ft_printf("-----------------------------------------\n\n"); */
		sauron(&base);
/* 		ft_printf("-----------------------------------------\n");
		print_tokens(base.token); */
		free_base(&base);
		
		 
		ft_printf(GREEN"Exit code in main : %d\n"RESET, base.exit_code);
		free(input);
	}
	free_doubletab(&base.env);
	return (0);
}
