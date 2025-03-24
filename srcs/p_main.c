#include "../includes/minishell.h"

int	g_exit_status;

int main(void)
{
	t_base	base;
	char	*minitext;

	minitext = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&base, 0, sizeof(t_base));
	base.env = env_cpy();
	base.tild = ft_strdup(search_data_in_env(base.env, "HOME"));
	// header();
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
			return (free_doubletab(&base.env), ft_printf("exit\n"), clean_exit(&base), 0);
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
		if (!base.token)
			continue;
		identify_token(base.token);
		//print_tokens(base.token);
		base.token = token_parser(base.token);
		if (check_double_pippe(base.token) || check_only_redirect(base.token, &base))
		{
			add_history(base.input);
			free_null((void**)&base.input);
			continue ;
		}
		base.cmds = parsing_cmd(&base);
		identify_builtin(base.cmds);
		if (ft_strcmp(base.token->data, "exit") && !base.token->next)
			return (add_history(base.input), clean_exit(&base), 0);
		sauron(&base, 0, 0);
		add_history(base.input);
		free_base(&base);
	}
	free_doubletab(&base.env);
	rl_clear_history();
	return (0);
}
