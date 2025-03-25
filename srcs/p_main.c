#include "../includes/minishell.h"

int	g_exit_status;

int	main(void)
{
	t_base	base;
	char	*minitext;

	minitext = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	base_init(&base);
	while (1)
	{
		if (g_exit_status)
		{
			base.exit_code = g_exit_status;
			g_exit_status = 0;
		}
		minitext = minitext_rl(base.env, &base);
		base.input = readline(minitext);
		free_null((void **)&minitext);
		if (!base.input)
			return (free_doubletab(&base.env), ft_printf("exit\n"),
				clean_exit(&base), 0);
		if (base.input[0] == '\0' || base.input[0] == '\n')
		{
			free_null((void **)&base.input);
			continue ;
		}
		if (parser(base.input, &base))
		{
			add_history(base.input);
			free_null((void **)&base.input);
			continue ;
		}
		if (!base.token)
			continue ;
		sauron(&base, 0, 0);
		add_history(base.input);
		free_base(&base);
	}
	free_doubletab(&base.env);
	rl_clear_history();
	return (0);
}
