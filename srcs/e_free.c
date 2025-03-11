# include "../includes/minishell.h"


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
	t_token	*tmp;

	tkcpy = tk;
	while (tkcpy)
	{
		tmp = tkcpy;
		tkcpy = tkcpy->next;
		free_null((void **)&tmp->data);
		free(tmp);
	}
}

void	free_base(t_base *base)
{
	free_token_list(base->token);
	base->token = NULL;
	free_cmd_list(base->cmds);
	base->cmds = NULL;
	free_doubletab(&base->path_list);
	base->count_forks = 0;
}

/**Invalid read sur valgrind 
 * valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
 *  --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup
 *  ./minishell ls -l
 */
void	clean_exit(t_base *base, int exit_code)
{
	// A SUPPRE
	printf(GREEN "\texit code :%d\n "RESET, exit_code);
	base->exit_code = exit_code;
	free_base(base);
	exit (exit_code);
}
