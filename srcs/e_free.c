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

/* void printadr(t_token *tk)
{
	t_token	*tkcpy;

	tkcpy = tk;
	while (tkcpy)
	{
		if (tkcpy->data)
			printf("%s adresse : %p\n", tkcpy->data, &tkcpy->data);
		tkcpy = tkcpy->next;
	} 
} */

void	free_token_list(t_token *tk)
{
	t_token	*tkcpy;

	while (tk)
	{
		tkcpy = tk->next;
		free(tk->data);
		free(tk);
		tk = tkcpy; 
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
	printf(GREEN "\t clean exit -- exit code :%d\n "RESET, exit_code);
	base->exit_code = exit_code;
	free_base(base);
	exit (exit_code);
}
