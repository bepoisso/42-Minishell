#include "../includes/minishell.h"

/**
 * ==14954== 8 bytes in 1 blocks are definitely lost in loss record 3 of 78
 * ==14954==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
 * ==14954==    by 0x10BBDA: parsing_cmd (p_cmd.c:73)
 * ==14954==    by 0x10BF42: main (p_main.c:36)
 */
int main(void)
{
	t_base	base;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&base, 0, sizeof(t_base));
	base.input = NULL;
	base.env = env_cpy();
	header();
	while (1)
	{
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
			add_history(base.input);
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
