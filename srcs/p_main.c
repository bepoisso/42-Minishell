#include "../includes/minishell.h"

int main(void)
{
	t_base	base;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&base, 0, sizeof(t_base));
	base.input = NULL;
	header();
	while (1)
	{
		base.env = env_cpy();
		base.input = readline("🤏🐚> ");
		if (!base.input)
			return (free_doubletab(&base.env), ft_printf("exit\n"), 0);
		if (base.input[0] == '\0' || base.input[0] == '\n')
		{
			free_null((void**)&base.input);
			continue;
		}
		if (parser(base.input, &base))
		{
			free_null((void**)&base.input);
			continue;
		}
		identify_token(base.token);
		print_tokens(base.token);
		base.token = token_parser(base.token);
		if (check_only_redirect(base.token, &base))
		{
			free_null((void**)&base.input);
			continue ;
		}
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
		if (ft_strcmp(base.token->data, "exit") && !base.token->next)
			return (add_history(base.input), clean_exit(&base, 0), 0);
 		printf("-----------------------------------------\n");
 		print_tokens(base.token);
		ft_printf("\n\n\n");
		print_cmd(&base);
		ft_printf("-----------------------------------------\n\n");
		sauron(&base);
		add_history(base.input);
		ft_printf("-----------------------------------------\n");
		print_tokens(base.token);
		free_base(&base);
		//ft_printf(GREEN"Exit code in main : %d\n"RESET, base.exit_code);
	}
	return (0);
}
