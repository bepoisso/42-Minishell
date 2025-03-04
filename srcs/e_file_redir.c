#include "../includes/minishell.h"


/** Modifier fonction filechk pour prendre en compte les >> et <<
 * dans ces deux cas l'ouverture est differente pour ecrire a partir de la fin
 * dans le cas de >> et lire jusqu'au delimiteur dans le cas << 
 * utiliser l'optin de open O_APPEND
 * 
 * exemple de commande casse couille a gerer :
 * cat < input.txt > GESTION OK
 * cat < input.txt > outfile.txt GESTION OK
 * donc dans le cas un infile ou outfile apres, il faut aussi regarder si il 
 * y en a un autre apres car en l'etat je ne regarde que les commandes
 */
int	file_redir(t_token *tok, t_base *base)
{
	int	fd_in;
	int	fd_out;
	t_token	*tmp;

	tmp = tok;
	if (tmp->id == 3)
	{
		fd_in = filechk(tmp->next, 1, base);
		if (fd_in < 0)
			return (1);
		dup2(fd_in, STDIN_FILENO);
	}
	else if (tmp->id == 5)
	{
		fd_in = filechk(tmp->next, 1, base);
		if (fd_in < 0)
			return (1);
		dup2(fd_in, STDIN_FILENO);
	}
	if (tmp->id == 4)
	{
		fd_out = filechk(tmp->next, 2, base);
		if (fd_out < 0)
			return (1);
		dup2(fd_out, STDOUT_FILENO);
	}
	else if (tmp->id == 6)
	{
		fd_out = filechk(tmp->next, 3, base);
		if (fd_out < 0)
			return (1);
		dup2(fd_out, STDOUT_FILENO);
	}
	return(0);
}
