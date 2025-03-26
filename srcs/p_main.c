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
		minitext = minitext_rl(base.env, &base);
		base.input = readline(minitext);
		if (g_exit_status)
		{
			base.exit_code = g_exit_status;
			g_exit_status = 0;
		}
		free_null((void **)&minitext);
		if (!base.input)
			return (free_doubletab(&base.env), ft_printf("exit\n"),
				clean_exit(&base), 0);
		if (handling_error(&base))
			continue ;
		sauron(&base, 0, 0);
	}
	return (free_doubletab(&base.env), rl_clear_history(), 0);
}
