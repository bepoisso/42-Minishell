#include "../includes/minishell.h"

/*FONCTION SAURON
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		>>		redir outfile append
7		|		pipe
8		$		variable
9		cmd		commande
10		args	commande args */

void	sauron(t_base *base, int cmd_found, int redir_found)
{
	t_token	*tok;
	t_token	*tok_back;

	tok = base->token;
	init_exec(base);
	while (tok)
	{
		tok_back = tok;
		while (tok && tok->id != 7)
		{
			if (tok->id == 9)
			{
				prepare_exec(tok, base);
				cmd_found++;
			}
			else if (tok->id >= 3 && tok->id <= 6)
				redir_found ++;
			tok = tok->next;
			if (tok && tok->id == 7)
				tok = tok->next;
		}
		if (redir_found > 0 && cmd_found == 0)
			handle_redirec_alone(tok_back);
	}
	wait_rings(base);
}
