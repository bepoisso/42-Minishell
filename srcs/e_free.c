#include "../includes/minishell.h"

void	free_n_tabint(int **tabint, int n)
{
	while (n > 0)
	{
		n--;
		free_null((void **)&tabint[n]);
	}
	free(tabint);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*cmdcpy;
	t_cmd	*tmp;

	cmdcpy = cmd;
	while (cmdcpy)
	{
		tmp = cmdcpy;
		cmdcpy = cmdcpy->next;
		free_doubletab(&tmp->cmd);
		free_null((void **)&tmp->path_cmd);
		free(tmp);
	}
}

void	free_token_list(t_token *tk)
{
	t_token	*tkcpy;

	while (tk)
	{
		tkcpy = tk->next;
		free_null((void **)&tk->data);
		free_null((void **)&tk);
		tk = tkcpy;
	}
}

void	free_dollar_list(t_dollar *dollar)
{
	t_dollar	*dolcpy;

	while (dollar)
	{
		dolcpy = dollar->next;
		free_null((void **)&dollar->data);
		free_null((void **)&dollar->name);
		free_null((void **)&dollar);
		dollar = dolcpy;
	}
}

void	free_base(t_base *base)
{
	free_token_list(base->token);
	base->token = NULL;
	free_dollar_list(base->dollars);
	base->dollars = NULL;
	free_cmd_list(base->cmds);
	base->cmds = NULL;
	free_doubletab(&base->path_list);
	base->count_forks = 0;
	free_null((void **)&base->input);
}

void	clean_exit(t_base *base, int exit_code)
{
	base->exit_code = exit_code;
	free_base(base);
	exit (exit_code);
}
